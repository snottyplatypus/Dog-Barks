#pragma once
#include <string>

struct CommandedSystem;

class AiState
{
public:
	virtual ~AiState() {}
	virtual void enter(CommandedSystem & system) = 0;
	virtual void update(CommandedSystem & system) = 0;
	template <class T> void transit(CommandedSystem & system)
	{
		system._ai->_state = std::make_unique<T>();
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
	void update(CommandedSystem & system) override {}
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
	SurprisedState() { _id = "Surprised"; }
	~SurprisedState() {}
	void enter(CommandedSystem & system) override;
	void update(CommandedSystem & system) override;
};

class AttackingState : public AiState
{
public:
	AttackingState() { _id = "Surprised"; }
	~AttackingState() {}
	void enter(CommandedSystem & system) override;
	void update(CommandedSystem & system) override;
};