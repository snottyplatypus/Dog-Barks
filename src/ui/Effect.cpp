#include "Effect.hpp"
#include <algorithm>

void ShootEffect::update()
{
	if (_launch) {
		_timer = time;
		_active = true;
		_launch = false;
	}
	if (std::fmodf(time - _timer, _duration) <= _duration / 2.0f && _stop < _repeat) {
		TCODLine::line(_from._x, _from._y, _to._x, _to._y, &_line);
		_inc = true;
	}
	if (std::fmodf(time - _timer, _duration) >= _duration / 2.0f && _inc) {
		_stop++;
		_inc = false;
	}
	if (time - _timer > _duration * static_cast<float>(_repeat))
		reset();
}

void ShootEffect::reset()
{
	_active = false;
	_launch = false;
	_repeat = 1;
	_stop = 0;
	_from = { 0, 0 };
	_to = { 0, 0 };
}

void ShootEffect::create(PositionComponent& from, PositionComponent& to, PositionComponent& mod, PositionComponent& modDir)
{
	_from = from + mod;
	_to = to + mod + modDir;
	_launch = true;
}

void BloodEffect::create(PositionComponent& from, PositionComponent& dir, PositionComponent& mod, int time)
{
	_line._mod = mod;
	dir._x = std::min(dir._x, 3);
	dir._y = std::min(dir._y, 3);
	for (int i = 0; i < time; i++) {
		PositionComponent to = from + dir + PositionComponent{ rng.getInt(-2, 2), rng.getInt(-2, 2) };
		TCODLine::line(from._x, from._y, to._x, to._y, &_line);
	}
}

Effect::Effect()
{
	_shootEffect = std::make_shared<ShootEffect>();
	_bloodEffect = std::make_shared<BloodEffect>();
	_effects.push_back(_shootEffect);
}

Effect::~Effect()
{
}

void Effect::update()
{
	for (auto i : _effects)
		if ( i->_active || i->_launch )
			i->update();
}
