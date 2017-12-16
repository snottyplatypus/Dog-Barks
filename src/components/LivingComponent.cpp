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
	for (int i = 0; i < _parts.size(); i++)
		_keys[_parts[i]._name] = i;
}

void LivingComponent::update()
{
	for (int i = 0; i < _parts.size(); i++) {
		if (_parts[i]._bleeding)
			_parts[i]._hp -= 1;
		if (_parts[i]._shot)
			_parts[i]._bleeding = true;
		if (_parts[i]._hp <= 0)
			_parts[i]._ability = false;
		if (_parts[i]._abilityName == "live")
			if (_parts[i]._ability == false)
				_dead = true;
	}
	if (_dead)
		eventManager.onNotify(std::make_unique<DeathEvent>(), *_system.lock());
}

void LivingComponent::handleDamage(Weapon& weapon, BodyPart& target, int bullet)
{
	int bullet2 = rng.getInt(0, bullet - 1);
	bullet -= bullet2;
	target._hp -= bullet * weapon._projectiles * weapon._damage;
	target._shot = true;
	if (bullet2 > 0) {
		int part = rng.getInt(1, static_cast<int>(_parts.size()));
		BodyPart& target2 = _parts[part];
		target2._hp -= bullet * weapon._projectiles * weapon._damage;
		target2._shot = true;
	}
	update();
}

void LivingComponent::bodyInfo()
{
	std::cout << std::endl;
	std::cout << _system.lock()->_renderer->_name << std::endl;
	for (auto i : _parts) {
		std::cout << i._name << " : " << i._hp << " | " << i._bleeding << std::endl;
	}
}
