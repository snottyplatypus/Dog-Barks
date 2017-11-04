#pragma once
#include "../components/PositionComponent.hpp"
#include <cmath>

namespace db 
{

	template<typename T>
	T dist(PositionComponent& pos1, PositionComponent& pos2)
	{
		int dx = pos1._x - pos2._x;
		int dy = pos1._y - pos2._y;
		return static_cast<T>( std::sqrt( std::pow(dx, 2) + std::pow(dy, 2) ) );
	}

	template<typename T>
	T dist_sq(PositionComponent& pos1, PositionComponent& pos2) 
	{
		int dx = pos1._x - pos2._x;
		int dy = pos1._y - pos2._y;
		return static_cast<T>( std::pow(dx, 2) + std::pow(dy, 2) );
	}

	template<typename T>
	T dist_cb(PositionComponent& pos1, PositionComponent& pos2)
	{
		int dx = pos1._x - pos2._x;
		int dy = pos1._y - pos2._y;
		return static_cast<T>( std::pow( std::sqrt( std::pow(dx, 2) + std::pow(dy, 2) ), 3) );
	}

	template<typename T>
	T dist_dsq(PositionComponent& pos1, PositionComponent& pos2)
	{
		int dx = pos1._x - pos2._x;
		int dy = pos1._y - pos2._y;
		return static_cast<T>(std::pow(dx, 2) + std::pow(dy, 2));
	}
}