#pragma once
#include "../utils/EventManager.hpp"

template<typename T> struct Command
{
	virtual ~Command() {}

	virtual void execute(T& system) = 0;
};

template<typename T> struct Cancel : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify( CANCEL, system ); }
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
	void execute(T& system) override { eventManager.onNotify( TRIGGER_LOOKING_CURSOR, system ); }
};

template<typename T> struct FireCursorMode : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify( TRIGGER_FIRE_CURSOR, system ); }
};