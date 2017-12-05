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

enum Event
{
	NONE,
	CANCEL,
	MOVE,
	END_TURN,
	TRIGGER_ENTER,
	TRIGGER_LOOKING_CURSOR,
	TRIGGER_FIRE_CURSOR,
	LOOKING_TERRAIN,
	LOOKING_ACTOR,
	AIMING,
};

struct MoveEvent
{
	int _id = MOVE;
	int _x;
	int _y;
};

struct LookingEvent
{
	int _id;
	int _x;
	int _y;
	PositionComponent _from;
};