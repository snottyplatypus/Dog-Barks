#pragma once
#include <unordered_map>
#include <memory>
#include "../include/libtcod/libtcod.hpp"
#include <iostream>
#include "Command.hpp"

struct InputHandler
{
	InputHandler() 
	{
		//Arrows
		commands[TCODK_UP] = std::make_shared<MoveNorth<GameObjectSystem>>();
		commands[TCODK_RIGHT] = std::make_shared<MoveEast<GameObjectSystem>>();
		commands[TCODK_DOWN] = std::make_shared<MoveSouth<GameObjectSystem>>();
		commands[TCODK_LEFT] = std::make_shared<MoveWest<GameObjectSystem>>();
		//Num (for laptop)
		commands[TCODK_9] = std::make_shared<MoveNE<GameObjectSystem>>();
		commands[TCODK_8] = std::make_shared<MoveNorth<GameObjectSystem>>();
		commands[TCODK_7] = std::make_shared<MoveNW<GameObjectSystem>>();
		commands[TCODK_6] = std::make_shared<MoveEast<GameObjectSystem>>();
		commands[TCODK_4] = std::make_shared<MoveWest<GameObjectSystem>>();
		commands[TCODK_3] = std::make_shared<MoveSE<GameObjectSystem>>();
		commands[TCODK_2] = std::make_shared<MoveSouth<GameObjectSystem>>();
		commands[TCODK_1] = std::make_shared<MoveSW<GameObjectSystem>>();
		//Numpad
		commands[TCODK_KP9] = std::make_shared<MoveNE<GameObjectSystem>>();
		commands[TCODK_KP8] = std::make_shared<MoveNorth<GameObjectSystem>>();
		commands[TCODK_KP7] = std::make_shared<MoveNW<GameObjectSystem>>();
		commands[TCODK_KP6] = std::make_shared<MoveEast<GameObjectSystem>>();
		commands[TCODK_KP4] = std::make_shared<MoveWest<GameObjectSystem>>();
		commands[TCODK_KP3] = std::make_shared<MoveSE<GameObjectSystem>>();
		commands[TCODK_KP2] = std::make_shared<MoveSouth<GameObjectSystem>>();
		commands[TCODK_KP1] = std::make_shared<MoveSW<GameObjectSystem>>();
	}
	~InputHandler() {}

	void onObject(GameObjectSystem& system,  TCOD_key_t& key)
	{

		if (key.vk == TCODK_NONE)
			system._command = nullptr;
		else
			 system._command = commands[key.vk];
	}

private:
	std::unordered_map<int, std::shared_ptr<Command<GameObjectSystem>>> commands;
};

extern InputHandler inputHandler;