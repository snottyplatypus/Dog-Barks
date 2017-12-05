#pragma once
#include "../utils/EventManager.hpp"
#include <iostream>

template<typename T> struct Command
{
	virtual ~Command() {}

	virtual void execute(T& system) = 0;
};

template<typename T> struct Nothing : public Command<T>
{
	void execute(T& system) override {}
};

template<typename T> struct Cancel : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify(std::make_unique<TriggerCancel>(), system); }
};

template<typename T> struct Enter : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify(std::make_unique<TriggerEnter>(), system); }
};

template<typename T> struct MoveNorth : public Command<T>
{
	void execute(T& system) override { eventManager.onMove( {MOVE, 0, -1}, system ); }
};

template<typename T> struct MoveEast : public Command<T>
{
	void execute(T& system) override { eventManager.onMove( { MOVE, 1, 0 }, system); }
};

template<typename T> struct MoveSouth : public Command<T>
{
	void execute(T& system) override { eventManager.onMove( { MOVE, 0, 1 }, system); }
};

template<typename T> struct MoveWest : public Command<T>
{
	void execute(T& system) override { eventManager.onMove( { MOVE, -1, 0 }, system); }
};

template<typename T> struct MoveNE : public Command<T>
{
	void execute(T& system) override { eventManager.onMove( { MOVE, 1, -1 }, system); }
};

template<typename T> struct MoveSE : public Command<T>
{
	void execute(T& system) override { eventManager.onMove( { MOVE, 1, 1 }, system); }
};

template<typename T> struct MoveNW : public Command<T>
{
	void execute(T& system) override { eventManager.onMove( { MOVE, -1, -1 }, system); }
};

template<typename T> struct MoveSW : public Command<T>
{
	void execute(T& system) override { eventManager.onMove( { MOVE, -1, 1 }, system); }
};

template<typename T> struct LookingCursorMode : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify(std::make_unique<TriggerLookingMode>(), system ); }
};

template<typename T> struct AimingCursorMode : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify(std::make_unique<TriggerAimingMode>(), system ); }
};