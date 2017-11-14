#pragma once
#include <map>
#include <memory>
#include "../include/libtcod/libtcod.hpp"
#include "../utils/EventManager.hpp"
#include "../ui/Gui.hpp"
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
		_move['9'] = std::make_shared<MoveNE<GameObjectSystem>>();
		_move['8'] = std::make_shared<MoveNorth<GameObjectSystem>>();
		_move['7'] = std::make_shared<MoveNW<GameObjectSystem>>();
		_move['6'] = std::make_shared<MoveEast<GameObjectSystem>>();
		_move['4'] = std::make_shared<MoveWest<GameObjectSystem>>();
		_move['3'] = std::make_shared<MoveSE<GameObjectSystem>>();
		_move['2'] = std::make_shared<MoveSouth<GameObjectSystem>>();
		_move['1'] = std::make_shared<MoveSW<GameObjectSystem>>();
		
		//Cursors
		_interaction['l'] = std::make_shared<LookingCursorMode<CommandedSystem>>();
		_interaction['f'] = std::make_shared<FireCursorMode<CommandedSystem>>();

		//Pause menu & cancel
		_interaction[TCODK_ESCAPE] = std::make_shared<Cancel<CommandedSystem>>();
		_interaction[TCODK_ENTER] = std::make_shared<Enter<CommandedSystem>>();
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
		else if(key.vk == TCODK_TEXT)
			if(_move.find(key.text[0]) != _move.end())
				system._move = _move[key.text[0]];
			else if (_interaction.find(key.text[0]) != _interaction.end())
				system._interaction = _interaction[key.text[0]];
	}

	void onMenu(Gui& gui)
	{
		if (key.vk == TCODK_TEXT)
			gui._choice = key.text[0];
		else if (key.vk == TCODK_ENTER)
			gui._choice = 1;
	}

private:
	std::map<int, std::shared_ptr<Command<GameObjectSystem>>> _move;
	std::map<int, std::shared_ptr<Command<CommandedSystem>>> _interaction;
};

extern InputHandler inputHandler;