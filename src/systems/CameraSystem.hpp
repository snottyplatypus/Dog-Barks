#pragma once
#include <memory>
#include "../components/PositionComponent.hpp"

struct CameraSystem 
{
	CameraSystem() 
	{
		_pos = std::make_shared<PositionComponent>();
	}
	~CameraSystem() {}

	void lockOn(PositionComponent pos) 
	{
		_pos->_x = pos._x;
		_pos->_y = pos._y;
	}

	std::shared_ptr<PositionComponent> _pos;
};