#pragma once
#include <unordered_map>
#include <queue>
#include <memory>
#include "../include/rltk.hpp"
#include "Command.hpp"
#include <iostream>

template<typename T> struct InputHandler
{
	InputHandler() 
	{
		//Arrows
		commands[sf::Keyboard::Up] = std::make_shared<MoveNorth<T>>();
		commands[sf::Keyboard::Right] = std::make_shared<MoveEast<T>>();
		commands[sf::Keyboard::Down] = std::make_shared<MoveSouth<T>>();
		commands[sf::Keyboard::Left] = std::make_shared<MoveWest<T>>();
		//Num (for laptop)
		commands[sf::Keyboard::Num9] = std::make_shared<MoveNE<T>>();
		commands[sf::Keyboard::Num8] = std::make_shared<MoveNorth<T>>();
		commands[sf::Keyboard::Num7] = std::make_shared<MoveNW<T>>();
		commands[sf::Keyboard::Num6] = std::make_shared<MoveEast<T>>();
		commands[sf::Keyboard::Num4] = std::make_shared<MoveWest<T>>();
		commands[sf::Keyboard::Num3] = std::make_shared<MoveSE<T>>();
		commands[sf::Keyboard::Num2] = std::make_shared<MoveSouth<T>>();
		commands[sf::Keyboard::Num1] = std::make_shared<MoveSW<T>>();
		//Numpad
		commands[sf::Keyboard::Numpad9] = std::make_shared<MoveNE<T>>();
		commands[sf::Keyboard::Numpad8] = std::make_shared<MoveNorth<T>>();
		commands[sf::Keyboard::Numpad7] = std::make_shared<MoveNW<T>>();
		commands[sf::Keyboard::Numpad6] = std::make_shared<MoveEast<T>>();
		commands[sf::Keyboard::Numpad4] = std::make_shared<MoveWest<T>>();
		commands[sf::Keyboard::Numpad3] = std::make_shared<MoveSE<T>>();
		commands[sf::Keyboard::Numpad2] = std::make_shared<MoveSouth<T>>();
		commands[sf::Keyboard::Numpad1] = std::make_shared<MoveSW<T>>();
	}
	~InputHandler() {}

	std::shared_ptr<Command<T>> update()
	{
		if (rltk::get_window()->waitEvent(key.event))
			if(key.event.type == sf::Event::KeyPressed)
				return commands[key.event.key.code];
		return nullptr;
	}

private:
	std::unordered_map<int, std::shared_ptr<Command<T>>> commands;
	rltk::key_pressed_t key;
	sf::Event event;
};