#pragma once
#include <unordered_map>
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
		movement[TCODK_UP] = std::make_shared<MoveNorth<GameObjectSystem>>();
		movement[TCODK_RIGHT] = std::make_shared<MoveEast<GameObjectSystem>>();
		movement[TCODK_DOWN] = std::make_shared<MoveSouth<GameObjectSystem>>();
		movement[TCODK_LEFT] = std::make_shared<MoveWest<GameObjectSystem>>();
		//Num (for laptop)
		movement[TCODK_9] = std::make_shared<MoveNE<GameObjectSystem>>();
		movement[TCODK_8] = std::make_shared<MoveNorth<GameObjectSystem>>();
		movement[TCODK_7] = std::make_shared<MoveNW<GameObjectSystem>>();
		movement[TCODK_6] = std::make_shared<MoveEast<GameObjectSystem>>();
		movement[TCODK_4] = std::make_shared<MoveWest<GameObjectSystem>>();
		movement[TCODK_3] = std::make_shared<MoveSE<GameObjectSystem>>();
		movement[TCODK_2] = std::make_shared<MoveSouth<GameObjectSystem>>();
		movement[TCODK_1] = std::make_shared<MoveSW<GameObjectSystem>>();
		//Numpad
		movement[TCODK_KP9] = std::make_shared<MoveNE<GameObjectSystem>>();
		movement[TCODK_KP8] = std::make_shared<MoveNorth<GameObjectSystem>>();
		movement[TCODK_KP7] = std::make_shared<MoveNW<GameObjectSystem>>();
		movement[TCODK_KP6] = std::make_shared<MoveEast<GameObjectSystem>>();
		movement[TCODK_KP4] = std::make_shared<MoveWest<GameObjectSystem>>();
		movement[TCODK_KP3] = std::make_shared<MoveSE<GameObjectSystem>>();
		movement[TCODK_KP2] = std::make_shared<MoveSouth<GameObjectSystem>>();
		movement[TCODK_KP1] = std::make_shared<MoveSW<GameObjectSystem>>();
	}
	~InputHandler() {}

	void onObject(GameObjectSystem& system)
	{

		if (key.vk == TCODK_NONE)
			system._command = nullptr;
		else
			 system._command = movement[key.vk];
	}

private:
	std::unordered_map<int, std::shared_ptr<Command<GameObjectSystem>>> movement;
};

extern InputHandler inputHandler;