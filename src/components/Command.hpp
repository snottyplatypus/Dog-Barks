#pragma once

template<typename T> struct Command
{
	virtual ~Command() {}

	virtual void execute(T& system) = 0;
};

template<typename T> struct MoveNorth : public Command<T>
{
	void execute(T& system) override { --system.pos_->y_; }
};

template<typename T> struct MoveEast : public Command<T>
{
	void execute(T& system) override { ++system.pos_->x_; }
};

template<typename T> struct MoveSouth : public Command<T>
{
	void execute(T& system) override { ++system.pos_->y_; }
};

template<typename T> struct MoveWest : public Command<T>
{
	void execute(T& system) override { --system.pos_->x_; }
};

template<typename T> struct MoveNE : public Command<T>
{
	void execute(T& system) override { ++system.pos_->x_; --system.pos_->y_; }
};

template<typename T> struct MoveSE : public Command<T>
{
	void execute(T& system) override { ++system.pos_->x_; ++system.pos_->y_; }
};

template<typename T> struct MoveNW : public Command<T>
{
	void execute(T& system) override { --system.pos_->x_; --system.pos_->y_; }
};

template<typename T> struct MoveSW : public Command<T>
{
	void execute(T& system) override { --system.pos_->x_; ++system.pos_->y_; }
};