#include "AiState.hpp"
#include "../../systems/CommandedSystem.hpp"
#include "../level/Level.hpp"
#include <iostream>

std::vector<std::shared_ptr<CommandedSystem>> AiState::hostileInFov(CommandedSystem & system)
{
	std::vector<std::shared_ptr<CommandedSystem>> nearby;
	for (int i = system._pos->_x - system._computing->_radius; i < system._pos->_x + system._computing->_radius; ++i) {
		for (int j = system._pos->_y - system._computing->_radius; j < system._pos->_y + system._computing->_radius; ++j) {
			if (system._computing->_map->isInFov(i, j)) {
				auto k = level._terrain[i][j]._actor;
				if (k != nullptr)
					if (system._faction._relations[k->_faction._name] == "hostile")
						nearby.push_back(k);
			}
		}
	}
	return nearby;
}

void WanderingState::enter(CommandedSystem & system)
{
}

void WanderingState::update(CommandedSystem & system)
{
	std::cout << system._renderer->_name << " wandering\n";
	auto nearby = hostileInFov(system);
	if (!nearby.empty())
		transit<SurprisedState>(system, *nearby.front());
}

void SurprisedState::enter(CommandedSystem & system)
{
}

void SurprisedState::update(CommandedSystem & system)
{
	std::cout << system._renderer->_name << " surprised\n";
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
		std::cout << system._renderer->_name << " attacking " << _target._renderer->_name << std::endl;
	}
}

void ChasingState::enter(CommandedSystem & system)
{
}

void ChasingState::update(CommandedSystem & system)
{
	std::cout << system._renderer->_name << " chasing " << _target._x << " " << _target._y << std::endl;
	auto nearby = hostileInFov(system);
	if (!nearby.empty())
		transit<AttackingState>(system, *nearby.front());
}
