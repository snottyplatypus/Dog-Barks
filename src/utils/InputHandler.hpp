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
		actor[TCODK_UP] = std::make_shared<MoveNorth<GameObjectSystem>>();
		actor[TCODK_RIGHT] = std::make_shared<MoveEast<GameObjectSystem>>();
		actor[TCODK_DOWN] = std::make_shared<MoveSouth<GameObjectSystem>>();
		actor[TCODK_LEFT] = std::make_shared<MoveWest<GameObjectSystem>>();
		//Num (for laptop)
		actor[TCODK_9] = std::make_shared<MoveNE<GameObjectSystem>>();
		actor[TCODK_8] = std::make_shared<MoveNorth<GameObjectSystem>>();
		actor[TCODK_7] = std::make_shared<MoveNW<GameObjectSystem>>();
		actor[TCODK_6] = std::make_shared<MoveEast<GameObjectSystem>>();
		actor[TCODK_4] = std::make_shared<MoveWest<GameObjectSystem>>();
		actor[TCODK_3] = std::make_shared<MoveSE<GameObjectSystem>>();
		actor[TCODK_2] = std::make_shared<MoveSouth<GameObjectSystem>>();
		actor[TCODK_1] = std::make_shared<MoveSW<GameObjectSystem>>();
		//Numpad
		actor[TCODK_KP9] = std::make_shared<MoveNE<GameObjectSystem>>();
		actor[TCODK_KP8] = std::make_shared<MoveNorth<GameObjectSystem>>();
		actor[TCODK_KP7] = std::make_shared<MoveNW<GameObjectSystem>>();
		actor[TCODK_KP6] = std::make_shared<MoveEast<GameObjectSystem>>();
		actor[TCODK_KP4] = std::make_shared<MoveWest<GameObjectSystem>>();
		actor[TCODK_KP3] = std::make_shared<MoveSE<GameObjectSystem>>();
		actor[TCODK_KP2] = std::make_shared<MoveSouth<GameObjectSystem>>();
		actor[TCODK_KP1] = std::make_shared<MoveSW<GameObjectSystem>>();

		//LookingCursor
		actor['l'] = std::make_shared<LookingCursorMode<GameObjectSystem>>();
	}
	~InputHandler() {}

	void onObject(GameObjectSystem& system)
	{
		if (key.vk == TCODK_NONE)
			system._command = nullptr;
		else if (key.vk == TCODK_CHAR)
			system._command = actor[key.c];
		else
			system._command = actor[key.vk];
	}

private:
	std::unordered_map<int, std::shared_ptr<Command<GameObjectSystem>>> actor;
};

extern InputHandler inputHandler;