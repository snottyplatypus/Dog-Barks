#include "LevelGameState.hpp"
#include "Level.hpp"
#include "../utils/Global.hpp"
#include "../components/ai/AiState.hpp"
#include <libtcod/libtcod.hpp>
#include <iostream>

void GenerateState::enter(Level & level)
{
	level._player = data._player;
	level._player->_id = "player";
	level._player->init(level._width, level._height);
	level.updateComputingMap(*level._player);
	level._actors.push_back(level._player);

	level._camera.lockOn({ config.screenWidth / 2 - level._width / 2, config.screenHeight / 2 - level._height / 2 });
	update(level);
}

void GenerateState::update(Level & level)
{
	level.generateLevel();
	level._turnState->transit<PlayerTurn>(level);
	level._gameState->transit<RaidState>(level);
}

void RaidState::enter(Level & level)
{
	level.timeToAssault = rng.getInt(30, 60);
}

void RaidState::update(Level & level)
{
	for (auto i : level._actors) {
		level._terrain[i->_pos->_x][i->_pos->_y]._actor = i;
		i->_renderer->_bg = level._terrain[i->_pos->_x][i->_pos->_y]._renderer->_bg;
	}
	level._turnState->update(level);
	level._renderState->update(level);
	if (level.timeToAssault <= 0)
		transit<AssaultState>(level);
	TCODConsole::root->printEx(config.screenWidth / 2, 2, TCODConsole::root->getBackgroundFlag(), TCOD_CENTER, "Time until assault : %i", level.timeToAssault);
}

void AssaultState::enter(Level & level)
{
	int nOfficer = rng.getInt(config.MIN_OFFICER, config.MAX_OFFICER);
	for (int i = 0; i < nOfficer; i++) {
		level._actors.push_back(std::make_shared<CommandedSystem>(2 + i, 2));
		level._actors.back()->_renderer->_tile = "swat";
		level._actors.back()->init(level._width, level._height);
		level._actors.back()->_faction = data._factions["swat"];
		level._actors.back()->_renderer->_name = "swatman";
		int index = rng.getInt(1, static_cast<int>(data._wKeys.size()) - 1);
		level._actors.back()->_inventory->_held = data._weapons[data._wKeys[index]];
		bool hostile = false;
		for (auto i : level._actors) {
			if (level._actors.back()->_faction._relations[i->_faction._name] == "hostile" && !i->_body->_dead) {
				level._actors.back()->_ai->_state->transit<RaidingState>(*level._actors.back(), *i);
				hostile = true;
			}
		}
		if (!hostile)
			level._actors.back()->_ai->_state->transit<WanderingState>(*level._actors.back());
	}
}

void AssaultState::update(Level & level)
{
	for (auto i : level._actors) {
		level._terrain[i->_pos->_x][i->_pos->_y]._actor = i;
		i->_renderer->_bg = level._terrain[i->_pos->_x][i->_pos->_y]._renderer->_bg;
	}
	level._turnState->update(level);
	level._renderState->update(level);
	TCODConsole::root->printEx(config.screenWidth / 2, 2, TCODConsole::root->getBackgroundFlag(), TCOD_CENTER, "Dog barks !");
}
