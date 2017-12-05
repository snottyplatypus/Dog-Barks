#pragma once

class Level;

class LevelRenderState
{
public:
	virtual ~LevelRenderState() {};
	virtual void enter(Level& level) = 0;
	virtual void update(Level& level) = 0;
	virtual void exit(Level& level) = 0;
	template <class T> void transit(Level& level)
	{
		level._renderState = std::make_unique<T>();
		level._renderState->enter(level);
	}
};

class RenderBase : public LevelRenderState
{
public:
	RenderBase() {}
	~RenderBase() {}
	void enter(Level& level) override;
	void update(Level& level) override;
	void exit(Level& level) override;
};

class RenderCursorModeL : public RenderBase
{
public:
	RenderCursorModeL() {}
	~RenderCursorModeL() {}
	void enter(Level& level) override;
	void update(Level& level) override;
	void exit(Level& level) override;
};

class RenderCursorModeF : public RenderBase
{
public:
	RenderCursorModeF() {}
	~RenderCursorModeF() {}
	void enter(Level& level) override;
	void update(Level& level) override;
	void exit(Level& level) override;
};