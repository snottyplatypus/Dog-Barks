#pragma once
#include <unordered_map>
#include <memory>
#include "../include/libtcod/libtcod.hpp"
#include "Command.hpp"

template<typename T> struct InputHandler
{
	InputHandler() 
	{
		//Arrows
		commands[TCODK_UP] = std::make_shared<MoveNorth<T>>();
		commands[TCODK_RIGHT] = std::make_shared<MoveEast<T>>();
		commands[TCODK_DOWN] = std::make_shared<MoveSouth<T>>();
		commands[TCODK_LEFT] = std::make_shared<MoveWest<T>>();
		//Num (for laptop)
		commands[TCODK_9] = std::make_shared<MoveNE<T>>();
		commands[TCODK_8] = std::make_shared<MoveNorth<T>>();
		commands[TCODK_7] = std::make_shared<MoveNW<T>>();
		commands[TCODK_6] = std::make_shared<MoveEast<T>>();
		commands[TCODK_4] = std::make_shared<MoveWest<T>>();
		commands[TCODK_3] = std::make_shared<MoveSE<T>>();
		commands[TCODK_2] = std::make_shared<MoveSouth<T>>();
		commands[TCODK_1] = std::make_shared<MoveSW<T>>();
		//Numpad
		commands[TCODK_KP9] = std::make_shared<MoveNE<T>>();
		commands[TCODK_KP8] = std::make_shared<MoveNorth<T>>();
		commands[TCODK_KP7] = std::make_shared<MoveNW<T>>();
		commands[TCODK_KP6] = std::make_shared<MoveEast<T>>();
		commands[TCODK_KP4] = std::make_shared<MoveWest<T>>();
		commands[TCODK_KP3] = std::make_shared<MoveSE<T>>();
		commands[TCODK_KP2] = std::make_shared<MoveSouth<T>>();
		commands[TCODK_KP1] = std::make_shared<MoveSW<T>>();
	}
	~InputHandler() {}

	std::shared_ptr<Command<T>> update()
	{
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr);
		return commands[key.vk];
	}

private:
	std::unordered_map<int, std::shared_ptr<Command<T>>> commands;
	TCOD_key_t key;
};