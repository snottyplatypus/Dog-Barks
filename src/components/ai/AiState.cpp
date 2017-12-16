#include "AiState.hpp"
#include <libtcod/libtcod.hpp>
#include "../../systems/CommandedSystem.hpp"
#include "../level/Level.hpp"
#include "../utils/Global.hpp"
#include "../utils/Geometry.hpp"
#include <string>
#include <algorithm>
#include <iostream>

std::vector<std::shared_ptr<CommandedSystem>> AiState::hostileInFov(CommandedSystem & system)
{
	std::vector<std::shared_ptr<CommandedSystem>> nearby;
	for (int i = system._pos->_x - system._computing->_radius; i < system._pos->_x + system._computing->_radius; ++i) {
		for (int j = system._pos->_y - system._computing->_radius; j < system._pos->_y + system._computing->_radius; ++j) {
			if (system._computing->_map->isInFov(i, j)) {
				auto k = level._terrain[i][j]._actor;
				if (k != nullptr)
					if (system._faction._relations[k->_faction._name] == "hostile" && !k->_body->_dead)
						nearby.push_back(k);
			}
		}
	}
	std::sort(nearby.begin(), nearby.end(), 
		[&](const std::shared_ptr<CommandedSystem> a, const std::shared_ptr<CommandedSystem> b) -> bool 
	{ 
		return db::dist<double>(*system._pos, *a->_pos) < db::dist<double>(*system._pos, *a->_pos);
	});
	return nearby;
}

void WanderingState::enter(CommandedSystem & system)
{
}

void WanderingState::update(CommandedSystem & system)
{
	auto nearby = hostileInFov(system);
	if (!nearby.empty())
		transit<SurprisedState>(system, *nearby.front());
	else
		system._move = std::make_shared<Move<CommandedSystem>>(rng.getInt(-1, 1), rng.getInt(-1, 1));
}

void SurprisedState::enter(CommandedSystem & system)
{
}

void SurprisedState::update(CommandedSystem & system)
{
	auto nearby = hostileInFov(system);
	if (nearby.empty())
		transit<ChasingState>(system, _target);
	else
		transit<AttackingState>(system, _target);
}

void AttackingState::enter(CommandedSystem & system)
{
}

void AttackingState::update(CommandedSystem & system)
{
	auto nearby = hostileInFov(system);
	if (nearby.empty())
		transit<ChasingState>(system, _target);
	else {
		_target = *nearby.front();
		std::string part = _target._body->_parts[rng.getInt(0, static_cast<int>(_target._body->_parts.size() - 1))]._name;
		int bullets = rng.getInt(1, system._inventory->_held._mag);
		system._interaction = std::make_shared<Attack<CommandedSystem>>(*_target._pos, part, 1);
	}
}

void ChasingState::enter(CommandedSystem & system)
{
	system._computing->_path->compute(system._pos->_x, system._pos->_y, _target._x, _target._y);
}

void ChasingState::update(CommandedSystem & system)
{
	auto nearby = hostileInFov(system);
	if (!nearby.empty())
		transit<AttackingState>(system, *nearby.front());
	else if (*system._pos != _target) {
		int dx = system._pos->_x;
		int dy = system._pos->_y;
		system._computing->_path->walk(&dx, &dy, true);
		system._move = std::make_shared<Move<CommandedSystem>>(dx - system._pos->_x, dy - system._pos->_y);
	}
	else
		transit<WanderingState>(system);
}
