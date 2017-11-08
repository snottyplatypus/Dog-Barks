#include "LivingComponent.hpp"
#include "../systems/CommandedSystem.hpp"

LivingComponent::LivingComponent()
{
}

LivingComponent::~LivingComponent()
{
}

void LivingComponent::init(std::shared_ptr<CommandedSystem> system)
{
	_system = system;
	_dead = false;
	for (int i = 0; i < _body.size(); i++)
		_keys[_body[i]._name] = i;
}

void LivingComponent::update()
{
	for (int i = 0; i < _body.size(); i++) {
		if (_body[i]._bleeding)
			_body[i]._hp -= 1;
		if (_body[i]._shot)
			_body[i]._bleeding = true;
		if (_body[i]._hp <= 0)
			_body[i]._ability = false;
		if (_body[i]._abilityName == "live")
			if (_body[i]._ability == false)
				_dead = true;
	}
	if (_dead)
		eventManager.onDeath(*_system.lock());
}

void LivingComponent::handleDamage(Weapon& weapon, BodyPart& target, int bullet)
{
	std::cout << bullet << std::endl;
	int bullet2 = rng.getInt(0, bullet - 1);
	bullet -= bullet2;
	target._hp -= bullet * weapon._projectiles * weapon._damage;
	target._shot = true;
	if (bullet2 > 0) {
		int part = rng.getInt(1, static_cast<int>(_body.size()));
		BodyPart& target2 = _body[part];
		target2._hp -= bullet * weapon._projectiles * weapon._damage;
		target2._shot = true;
	}
	update();
}

void LivingComponent::bodyInfo()
{
	std::cout << std::endl;
	std::cout << _system.lock()->_renderer->_name << std::endl;
	for (auto i : _body) {
		std::cout << i._name << " : " << i._hp << " | " << i._bleeding << std::endl;
	}
}
