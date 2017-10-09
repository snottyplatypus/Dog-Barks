#pragma once
#include <memory>
class ActorSystem;

template<typename T> struct Command
{
	virtual ~Command() {}

	virtual void execute(std::shared_ptr<T> system) = 0;
};

template<typename T> struct MoveEast : public Command<T>
{
	void execute(T &system) override { system.pos_->x_++ }
};
