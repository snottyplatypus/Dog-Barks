#pragma once
#include "../components/PositionComponent.hpp"

struct CommandedSystem;

class BaseEvent
{
public:
	virtual ~BaseEvent() {}
	virtual void react(CommandedSystem & object) = 0;
};

class EndTurn : public BaseEvent
{
public:
	EndTurn() {}
	~EndTurn() {}
	void react(CommandedSystem & object) override;
};

class TriggerLookingMode : public BaseEvent
{
public:
	TriggerLookingMode() {}
	~TriggerLookingMode() {}
	void react(CommandedSystem & object) override;
};

class TriggerAimingMode : public BaseEvent
{
public:
	TriggerAimingMode() {}
	~TriggerAimingMode() {}
	void react(CommandedSystem & object) override;
};

class TriggerEnter : public BaseEvent
{
public:
	TriggerEnter() {}
	~TriggerEnter() {}
	void react(CommandedSystem & object) override;
};

class TriggerCancel : public BaseEvent
{
public:
	TriggerCancel() {}
	~TriggerCancel() {}
	void react(CommandedSystem & object) override;
};

class MoveEvent : public BaseEvent
{
public:
	MoveEvent(int x, int y) : _x(x), _y(y) {}
	~MoveEvent() {}
	void react(CommandedSystem & object) override;

private:
	int _x;
	int _y;
};

class DeathEvent : public BaseEvent
{
public:
	DeathEvent() {}
	~DeathEvent() {}
	void react(CommandedSystem & object) override;
};

class LookingEvent : public BaseEvent
{
public:
	LookingEvent(int x, int y) : _x(x), _y(y) {}
	~LookingEvent() {}
	void react(CommandedSystem & object) override;

private:
	int _x;
	int _y;
};

class AimingEvent : public BaseEvent
{
public:
	AimingEvent(int x, int y) : _x(x), _y(y) {}
	~AimingEvent() {}
	void react(CommandedSystem & object) override;

private:
	int _x;
	int _y;
};
