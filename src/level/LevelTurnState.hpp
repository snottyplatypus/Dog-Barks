#pragma once
#include <string>
#include <memory>

class Level;

class LevelTurnState
{
public:
	virtual ~LevelTurnState() {};
	virtual void enter(Level& level) = 0;
	virtual void update(Level& level) = 0;
	virtual void exit(Level& level) = 0;
	template <class T> void transit(Level& level)
	{
		level._turnState = std::make_unique<T>();
		level._turnState->enter(level);
	}

	std::string _id;
};

class PlayerTurn : public LevelTurnState
{
public:
	PlayerTurn() { _id = "PlayerTurn"; }
	~PlayerTurn() {}
	void enter(Level& level) override;
	void update(Level& level) override;
	void exit(Level& level) override;
};

class OtherTurn : public LevelTurnState
{
public:
	OtherTurn() { _id = "OtherTurn"; }
	~OtherTurn() {}
	void enter(Level& level) override;
	void update(Level& level) override;
	void exit(Level& level) override;
};

class CursorModeL : public LevelTurnState
{
public:
	CursorModeL() { _id = "CursorModeL"; }
	~CursorModeL() {}
	void enter(Level& level) override;
	void update(Level& level) override;
	void exit(Level& level) override;
};

class CursorModeF : public LevelTurnState
{
public:
	CursorModeF() { _id = "CursorModeF"; }
	~CursorModeF() {}
	void enter(Level& level) override;
	void update(Level& level) override;
	void exit(Level& level) override;
};
