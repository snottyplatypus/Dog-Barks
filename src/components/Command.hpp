#pragma once
#include "../utils/EventManager.hpp"
#include <iostream>

template<typename T> struct Command
{
	virtual ~Command() {}

	virtual void execute(T& system) = 0;
};

template<typename T> struct MoveNorth : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify( {MOVE, 0, -1}, system ); }
};

template<typename T> struct MoveEast : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify({ MOVE, 1, 0 }, system); }
};

template<typename T> struct MoveSouth : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify({ MOVE, 0, 1 }, system); }
};

template<typename T> struct MoveWest : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify({ MOVE, -1, 0 }, system); }
};

template<typename T> struct MoveNE : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify({ MOVE, 1, -1 }, system); }
};

template<typename T> struct MoveSE : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify({ MOVE, 1, 1 }, system); }
};

template<typename T> struct MoveNW : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify({ MOVE, -1, -1 }, system); }
};

template<typename T> struct MoveSW : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify({ MOVE, -1, 1 }, system); }
};