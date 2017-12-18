#include "Event.hpp"
#include "EventManager.hpp"
#include "../level/Level.hpp"
#include "../ui/Gui.hpp"
#include "../ui/GuiState.hpp"
#include "../components/ai/AiState.hpp"
#include "../utils/EventManager.hpp"
#include <iostream>

void EndTurn::react(CommandedSystem & object)
{
	if (level._turnState->_id == "PlayerTurn") {
		if (object._id == "player") {
			object._updated = false;
			level._turnState->transit<OtherTurn>(level);
		}
	}
	else if (level._turnState->_id == "OtherTurn") {
		bool updated = true;
		for (std::size_t i = 1; i < level._actors.size(); ++i)
			if (!level._actors[i] ->_updated)
				updated = false;
		if (updated)
			level._turnState->transit<PlayerTurn>(level);
	}
}

void TriggerLookingMode::react(CommandedSystem & object)
{
	if (gui._state->_id == "Nothing") {
		level._turnState->transit<CursorModeL>(level);
		level._lookingCursor._pos->_x = level._player->_pos->_x;
		level._lookingCursor._pos->_y = level._player->_pos->_y;
	}
}

void TriggerAimingMode::react(CommandedSystem & object)
{
	if (gui._state->_id == "Nothing") {
		if (!level._player->_body->_dead) {
			level._turnState->transit<CursorModeF>(level);
			level._fireCursor._pos->_x = level._player->_pos->_x;
			level._fireCursor._pos->_y = level._player->_pos->_y;
		}
	}
}

void TriggerEnter::react(CommandedSystem & object)
{
	if (level._turnState->_id == "CursorModeF") {
		level._turnState->exit(level);
		eventManager.onAttack(object, level._fireCursor._lastPos, gui._attackSelect._bodyPart, gui._attackSelect._bullets);
		object._updated = true;
	}
}

void TriggerCancel::react(CommandedSystem & object)
{
	level._turnState->exit(level);
}

void MoveEvent::react(CommandedSystem & object)
{
	if (object._id != "cursor") {
		if (!object._body->_dead) {
			if (level._terrain[object._pos->_x + _x][object._pos->_y + _y]._isWalkable) {
				auto obj = level._terrain[object._pos->_x][object._pos->_y]._actor;
				if (level._terrain[object._pos->_x + _x][object._pos->_y + _y]._actor != nullptr) {
					auto temp = std::make_shared<CommandedSystem>(*level._terrain[object._pos->_x + _x][object._pos->_y + _y]._actor);
					level._terrain[object._pos->_x + _x][object._pos->_y + _y]._actor = obj;
					level._terrain[object._pos->_x][object._pos->_y]._actor = temp;
					temp->_pos->_x -= _x;
					temp->_pos->_y -= _y;
				}
				else {
					level._terrain[object._pos->_x][object._pos->_y]._actor = nullptr;
					level._terrain[object._pos->_x + _x][object._pos->_y + _y]._actor = obj;
				}

				object._pos->_x += _x;
				object._pos->_y += _y;
			}
		}
	}
	else {
		if (!level._terrain[object._pos->_x + _x][object._pos->_y + _y]._void) {
			object._pos->_x += _x;
			object._pos->_y += _y;
			if (gui._state->_id == "InspectingTerrain")
				gui._state->transit<LookingTerrain>(gui);
			else if (gui._state->_id == "AimPart" || gui._state->_id == "AimRound")
				gui._state->transit<AimTarget>(gui);
		}
	}
}

void DeathEvent::react(CommandedSystem & object)
{
	if (object._body->_dead) {
		object._renderer->_fg = TCODColor::darkRed;
		if (object._renderer->_name.find(" - dead") == std::string::npos)
			object._renderer->_name += " - dead";
		if (object._renderer->_tile.find("_dead") == std::string::npos)
			object._renderer->_tile += "_dead";
		object._ai->_state = std::make_unique<NoAi>();
	}
}

void LookingEvent::react(CommandedSystem & object)
{
	if (gui._state->_id == "LookingTerrain")
		if (object._computing->_map->isInFov(_x, _y))
			gui._state = std::make_unique<LookingTerrain>(PositionComponent{ _x, _y });
}

void AimingEvent::react(CommandedSystem & object)
{
	if (gui._state->_id == "AimTarget" || gui._state->_id == "Nothing") {
		auto target = level._terrain[_x][_y]._actor;
		if (object._computing->_map->isInFov(_x, _y))
			if (target != nullptr)
				gui._state = std::make_unique<AimTarget>(*target, object._inventory->_held._mag);
	}
}

void EscapeEvent::react(CommandedSystem & object)
{
	level._gameState->transit<EscapedState>(level);
}
