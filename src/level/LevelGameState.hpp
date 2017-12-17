#pragma once

class Level;

class LevelGameState
{
public:
	virtual ~LevelGameState() {};
	virtual void enter(Level& level) = 0;
	virtual void update(Level& level) = 0;
	template <class T> void transit(Level& level)
	{
		level._gameState = std::make_unique<T>();
		level._gameState->enter(level);
	}
};

class GenerateState : public LevelGameState
{
public:
	GenerateState() {}
	~GenerateState() {}
	void enter(Level& level) override;
	void update(Level& level) override;
};

class RaidState : public LevelGameState
{
public:
	RaidState() {}
	~RaidState() {}
	void enter(Level& level) override;
	void update(Level& level) override;
};

class AssaultState : public LevelGameState
{
public:
	AssaultState() {}
	~AssaultState() {}
	void enter(Level& level) override;
	void update(Level& level) override;
};
