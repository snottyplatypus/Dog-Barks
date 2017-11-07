#pragma once
#include "../include/libtcod/libtcod.hpp"
#include "../components/PositionComponent.hpp"
#include "../utils/Global.hpp"
#include "../utils/Line.hpp"
#include <vector>
#include <memory>
#include <iostream>

struct BaseEffect
{
	BaseEffect() : _active(false), _timer(0) {}
	virtual ~BaseEffect() {}
	virtual void update() = 0;

	bool _active;
	bool _launch;
	float _timer;
};

struct ShootEffect : public BaseEffect
{
	ShootEffect() : _repeat(1), _stop(0), _duration(0.15f), _inc(false) { _line._bg = TCODColor::white; }
	~ShootEffect() {}
	void update() override;
	void reset();
	void create(PositionComponent& from, PositionComponent& to, PositionComponent& mod, PositionComponent& modDir = PositionComponent{ 0, 0 });

private:
	int _repeat;
	int _stop;
	bool _inc;
	float _duration;
	PhysicalLine _line;
	PositionComponent _from;
	PositionComponent _to;
};

struct BloodEffect : public BaseEffect
{
	BloodEffect()
	{ 
		_active = true;
		_line._bg = TCODColor::red; 
	}
	~BloodEffect() {}
	void update() override {}
	void create(PositionComponent& from, PositionComponent& dir, PositionComponent& mod, int time = 1);

private:
	BloodLine _line;
};

class Effect
{
public:
	Effect();
	~Effect();
	void update();

	std::shared_ptr<ShootEffect> _shootEffect;
	std::shared_ptr<BloodEffect> _bloodEffect;
	std::vector<std::shared_ptr<BaseEffect>> _effects;
};