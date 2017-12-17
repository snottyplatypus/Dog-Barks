#pragma once
#include "../components/PositionComponent.hpp"
#include "../systems/CommandedSystem.hpp"
#include "../utils/EventManager.hpp"
#include <memory>
#include <string>
#include <vector>

class AiState
{
public:
	virtual ~AiState() {}
	virtual void enter(CommandedSystem & system) = 0;
	virtual void update(CommandedSystem & system) = 0;
	std::vector<std::shared_ptr<CommandedSystem>> hostileInFov(CommandedSystem & system);
	template <class T> void transit(CommandedSystem & system)
	{
		system._ai->_state = std::make_unique<T>();
		system._ai->_state->enter(system);
	}
	template <class T> void transit(CommandedSystem & system, CommandedSystem & target)
	{
		system._ai->_state = std::make_unique<T>(target);
		system._ai->_state->enter(system);
	}

	std::string _id;
};

class NoAi : public AiState
{
public:
	NoAi() { _id = "NoAi"; }
	~NoAi() {}
	void enter(CommandedSystem & system) override {}
	void update(CommandedSystem & system) override;
};

class WanderingState : public AiState
{
public:
	WanderingState() { _id = "Wandering"; }
	~WanderingState() {}
	void enter(CommandedSystem & system) override;
	void update(CommandedSystem & system) override;
};

class SurprisedState : public AiState
{
public:
	SurprisedState(const CommandedSystem & target) : _target(target) { _id = "Surprised"; }
	~SurprisedState() {}
	void enter(CommandedSystem & system) override;
	void update(CommandedSystem & system) override;

	CommandedSystem _target;
};

class AttackingState : public AiState
{
public:
	AttackingState(const CommandedSystem & target) : _target(target) { _id = "Attacking"; }
	~AttackingState() {}
	void enter(CommandedSystem & system) override;
	void update(CommandedSystem & system) override;

	CommandedSystem _target;
};

class ChasingState : public AiState
{
public:
	ChasingState(const CommandedSystem & target) : _target(*target._pos) { _id = "Chasing"; }
	~ChasingState() {}
	void enter(CommandedSystem & system) override;
	void update(CommandedSystem & system) override;

	PositionComponent _target;
};

class RaidingState : public AiState
{
public:
	RaidingState(const CommandedSystem & target) : _target(target) { _id = "Raiding	"; }
	~RaidingState() {}
	void enter(CommandedSystem & system) override;
	void update(CommandedSystem & system) override;

	CommandedSystem _target;
};