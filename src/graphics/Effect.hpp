#pragma once
#include "../include/libtcod/libtcod.hpp"
#include "../components/PositionComponent.hpp"
#include "../utils/Global.hpp"
#include "../systems/FireCursor.hpp"
#include <vector>
#include <memory>
#include <iostream>

struct BaseEffect
{
	BaseEffect() : _active(false), _timer(0) {}
	virtual ~BaseEffect() {}
	virtual void update() = 0;
	virtual void reset() = 0;

	bool _active;
	bool _launch;
	float _timer;
};

struct ShootEffect : public BaseEffect
{
	ShootEffect() : _repeat(3), _stop(0), _duration(0.15f), _inc(false) { _line._bg = TCODColor::white; }
	~ShootEffect() {}
	void update() override 
	{
		if ( _launch ) {
			_timer = time;
			_active = true;
			_launch = false;
		}
		if (std::fmodf(time - _timer, _duration) <= _duration/2.0f && _stop < _repeat) {
			TCODLine::line(_from._x, _from._y, _to._x, _to._y, &_line);
			_inc = true;
		}
		if (std::fmodf(time - _timer, _duration) >= _duration/2.0f && _inc) {
			_stop++;
			_inc = false;
		}
		if (time - _timer > _duration * static_cast<float>(_repeat))
			reset();
	}

	void reset() override
	{
		_active = false;
		_launch = false;
		_stop = 0;
		_from = { 0, 0 };
		_to = { 0, 0 };
	}

	int _repeat;
	int _stop;
	bool _inc;
	float _duration;
	FireLine _line;
	PositionComponent _from;
	PositionComponent _to;
};

class Effect
{
public:
	Effect();
	~Effect();
	void update();

	std::shared_ptr<ShootEffect> _shootEffect;
	std::vector<std::shared_ptr<BaseEffect>> _effects;
};