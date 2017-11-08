#pragma once
#include "../include/libtcod/libtcod.hpp"
#include "../components/PositionComponent.hpp"

class PhysicalLine : public TCODLineListener {
public:
	bool putPoint(int x, int y);

	TCODColor _bg;
	PositionComponent _lastPos;
};

class BloodLine : public TCODLineListener {
public:
	bool putPoint(int x, int y);

	TCODColor _bg;
	PositionComponent _mod;
};