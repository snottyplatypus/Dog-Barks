#include "Effect.hpp"

enum EffectType 
{
	SHOOTING_EFFECT,
};

Effect::Effect()
{
	_shootEffect = std::make_shared<ShootEffect>();
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
