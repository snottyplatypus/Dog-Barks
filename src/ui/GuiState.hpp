#pragma once
#include <string>
#include "../components/PositionComponent.hpp"
#include "../systems/CommandedSystem.hpp"
#include <iostream>

class Gui;

class GuiState
{
public:
	virtual ~GuiState() {}
	virtual void enter(Gui & gui) = 0;
	virtual void update(Gui & gui) = 0;
	virtual void next(Gui & gui) = 0;
	virtual void exit(Gui & gui) = 0;
	template <class T> void transit(Gui & gui)
	{
		gui._state = std::make_unique<T>();
		gui._state->enter(gui);
	}

	std::string _id;
};

class DefaultState : public GuiState
{
public:
	DefaultState() { _id = "Nothing"; }
	~DefaultState() {}
	void enter(Gui & gui) override {}
	void update(Gui & gui) override;
	void next(Gui & gui) override {}
	void exit(Gui & gui) override {}
};

class LookingTerrain : public DefaultState
{
public:
	LookingTerrain(PositionComponent target = { 0, 0 }) : _target(target) { _id = "LookingTerrain"; }
	~LookingTerrain() {}
	void enter(Gui & gui) override {}
	void update(Gui & gui) override;
	void next(Gui & gui) override;
	void exit(Gui & gui) override;

private:
	PositionComponent _target;
};

class InspectingTerrain : public DefaultState
{
public:
	InspectingTerrain(PositionComponent target, char choice) : _target(target), _choice(choice) { _id = "InspectingTerrain"; }
	~InspectingTerrain() {}
	void enter(Gui & gui) override {}
	void update(Gui & gui) override;
	void next(Gui & gui) override {}
	void exit(Gui & gui) override;

private:
	PositionComponent _target;
	char _choice;
};

class AimTarget : public DefaultState
{
public:
	AimTarget(CommandedSystem target = CommandedSystem(), int mag = 0) : _target(target), _mag(mag) { _id = "AimTarget"; }
	~AimTarget() {}
	void enter(Gui & gui) override {}
	void update(Gui & gui) override;
	void next(Gui & gui) override;
	void exit(Gui & gui) override;

private:
	CommandedSystem _target;
	int _mag;
};

class AimPart : public DefaultState
{
public:
	AimPart(CommandedSystem target = CommandedSystem(), int mag = 0) : _target(target), _mag(mag) { _id = "AimPart"; }
	~AimPart() {}
	void enter(Gui & gui) override {}
	void update(Gui & gui) override;
	void next(Gui & gui) override;
	void exit(Gui & gui) override;

private:
	CommandedSystem _target;
	int _mag;
};

class AimRound : public DefaultState
{
public:
	AimRound(CommandedSystem target = CommandedSystem(), int mag = 0) : _target(target), _mag(mag) { _id = "AimRound"; }
	~AimRound() {}
	void enter(Gui & gui) override {}
	void update(Gui & gui) override;
	void next(Gui & gui) override;
	void exit(Gui & gui) override;

private:
	CommandedSystem _target;
	int _mag;
};
