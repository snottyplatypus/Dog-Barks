#pragma once
#include <map>
#include <memory>
#include "../include/libtcod/libtcod.hpp"
#include "Global.hpp"
#include <iostream>
#include "Command.hpp"

struct InputHandler
{
	InputHandler() 
	{
		//Arrows
		_move[TCODK_UP] = std::make_shared<MoveNorth<GameObjectSystem>>();
		_move[TCODK_RIGHT] = std::make_shared<MoveEast<GameObjectSystem>>();
		_move[TCODK_DOWN] = std::make_shared<MoveSouth<GameObjectSystem>>();
		_move[TCODK_LEFT] = std::make_shared<MoveWest<GameObjectSystem>>();
		//Num (for laptop)
		_move[TCODK_9] = std::make_shared<MoveNE<GameObjectSystem>>();
		_move[TCODK_8] = std::make_shared<MoveNorth<GameObjectSystem>>();
		_move[TCODK_7] = std::make_shared<MoveNW<GameObjectSystem>>();
		_move[TCODK_6] = std::make_shared<MoveEast<GameObjectSystem>>();
		_move[TCODK_4] = std::make_shared<MoveWest<GameObjectSystem>>();
		_move[TCODK_3] = std::make_shared<MoveSE<GameObjectSystem>>();
		_move[TCODK_2] = std::make_shared<MoveSouth<GameObjectSystem>>();
		_move[TCODK_1] = std::make_shared<MoveSW<GameObjectSystem>>();
		//Numpad
		_move[TCODK_KP9] = std::make_shared<MoveNE<GameObjectSystem>>();
		_move[TCODK_KP8] = std::make_shared<MoveNorth<GameObjectSystem>>();
		_move[TCODK_KP7] = std::make_shared<MoveNW<GameObjectSystem>>();
		_move[TCODK_KP6] = std::make_shared<MoveEast<GameObjectSystem>>();
		_move[TCODK_KP4] = std::make_shared<MoveWest<GameObjectSystem>>();
		_move[TCODK_KP3] = std::make_shared<MoveSE<GameObjectSystem>>();
		_move[TCODK_KP2] = std::make_shared<MoveSouth<GameObjectSystem>>();
		_move[TCODK_KP1] = std::make_shared<MoveSW<GameObjectSystem>>();

		//Cursors
		_interaction['l'] = std::make_shared<LookingCursorMode<CommandedSystem>>();
		_interaction['f'] = std::make_shared<FireCursorMode<CommandedSystem>>();

		//Pause menu & cancel
		_interaction[TCODK_ESCAPE] = std::make_shared<Cancel<CommandedSystem>>();
	}
	~InputHandler() {}

	void onObject(CommandedSystem& system)
	{
		if (key.vk == TCODK_NONE) {
			system._move = nullptr;
			system._interaction = nullptr;
		}
		else if (_move.find(key.vk) != _move.end())
			system._move = _move[key.vk];
		else if (_interaction.find(key.vk) != _interaction.end())
			system._interaction = _interaction[key.vk];
		else if (_interaction.find(key.c) != _interaction.end())
			system._interaction = _interaction[key.c];
	}

private:
	std::map<int, std::shared_ptr<Command<GameObjectSystem>>> _move;
	std::map<int, std::shared_ptr<Command<CommandedSystem>>> _interaction;
};

extern InputHandler inputHandler;