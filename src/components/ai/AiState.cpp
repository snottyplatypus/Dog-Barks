#include "AiState.hpp"
#include "../../systems/CommandedSystem.hpp"
#include "../level/Level.hpp"
#include <iostream>

void WanderingState::enter(CommandedSystem & system)
{
}

void WanderingState::update(CommandedSystem & system)
{
	std::cout << system._renderer->_name << " wandering\n";
	for (int i = system._pos->_x - system._computing->_radius; i < system._pos->_x + system._computing->_radius; ++i) {
		for (int j = system._pos->_y - system._computing->_radius; j < system._pos->_y + system._computing->_radius; ++j) {
			if (system._computing->_map->isInFov(i, j)) {
				auto k = level._terrain[i][j]._actor;
				if (k != nullptr) {
					if (system._faction._relations[k->_faction._name] == "hostile") {
						transit<SurprisedState>(system);
					}
				}
			}
		}
	}
}

void SurprisedState::enter(CommandedSystem & system)
{
}

void SurprisedState::update(CommandedSystem & system)
{
	std::cout << system._renderer->_name << " surprised\n";
	for (int i = system._pos->_x - system._computing->_radius; i < system._pos->_x + system._computing->_radius; ++i) {
		for (int j = system._pos->_y - system._computing->_radius; j < system._pos->_y + system._computing->_radius; ++j) {
			if (system._computing->_map->isInFov(i, j)) {
				auto k = level._terrain[i][j]._actor;
				if (k != nullptr) {
					if (system._faction._relations[k->_faction._name] == "hostile") {
						transit<AttackingState>(system);
					}
				}
			}
		}
	}
}

void AttackingState::enter(CommandedSystem & system)
{
}

void AttackingState::update(CommandedSystem & system)
{
	for (int i = system._pos->_x - system._computing->_radius; i < system._pos->_x + system._computing->_radius; ++i) {
		for (int j = system._pos->_y - system._computing->_radius; j < system._pos->_y + system._computing->_radius; ++j) {
			if (system._computing->_map->isInFov(i, j)) {
				auto k = level._terrain[i][j]._actor;
				if (k != nullptr)
					if (system._faction._relations[k->_faction._name] == "hostile")
						std::cout << system._renderer->_name << " attacking " << k->_renderer->_name << std::endl;
			}
		}
	}
}
