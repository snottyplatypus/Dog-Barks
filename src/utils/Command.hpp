#pragma once
#include "../utils/EventManager.hpp"
#include "../components/PositionComponent.hpp"
#include <iostream>
#include <string>

template<typename T> struct Command
{
	virtual ~Command() {}
	virtual void execute(T& system) = 0;
};

template<typename T> struct Nothing : public Command<T>
{
	void execute(T& system) override { system._updated = true; eventManager.onNotify(std::make_unique<EndTurn>(), system); }
};

template<typename T> struct Cancel : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify(std::make_unique<TriggerCancel>(), system); }
};

template<typename T> struct Enter : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify(std::make_unique<TriggerEnter>(), system); }
};

template<typename T> struct Move : public Command<T>
{
	Move(int dx, int dy) : _dx(dx), _dy(dy) {}
	void execute(T& system) override { eventManager.onNotify(std::make_unique<MoveEvent>(_dx, _dy), system); }

	int _dx;
	int _dy;
};

template<typename T> struct LookingCursorMode : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify(std::make_unique<TriggerLookingMode>(), system ); }
};

template<typename T> struct AimingCursorMode : public Command<T>
{
	void execute(T& system) override { eventManager.onNotify(std::make_unique<TriggerAimingMode>(), system ); }
};

template<typename T> struct Attack : public Command<T>
{
	Attack(PositionComponent& target, std::string part, int bullets) : _target(target), _part(part), _bullets(bullets) {}
	void execute(T& system) override  { eventManager.onAttack(system, _target, _part, _bullets); }

	PositionComponent _target;
	std::string _part;
	int _bullets;
};