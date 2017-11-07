#pragma once
#include "../level/Item.hpp"
#include "../utils/Global.hpp"
#include "../utils/EventManager.hpp"
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

struct BodyPart
{
	std::string _name;
	int _hp;
	std::string _abilityName;
	bool _ability;
	bool _bleeding;
	int _size;
};

struct LivingComponent
{
	LivingComponent() {}
	~LivingComponent() {}

	void init()
	{
		_dead = false;
		for (auto i : _body)
			_keys.push_back(i.first);
	}

	void update()
	{
		for (auto i : _body) {
			if (i.second._abilityName == "live")
				if (i.second._ability == false)
					_dead = true;
		}
	}

	void handleDamage(Weapon& weapon, BodyPart& target, int bullet)
	{
		int bullet2 = rng.getInt(0, bullet - 1);
		bullet -= bullet2;
		target._hp -= bullet * weapon._projectiles * weapon._damage;
		if (target._hp < 0) {
			target._ability = false;
		}
		if (bullet2 > 0) {
			int part = rng.getInt(1, static_cast<int>(_keys.size()));
			BodyPart& target2 = _body[_keys[part]];
			target2._hp -= bullet * weapon._projectiles * weapon._damage;
			if (target2._hp <= 0)
				target2._ability = false;
		}
	} 

	void bodyInfo()
	{
		std::cout << std::endl;
		for (auto i : _body) {
			std::cout << i.second._name << " : " << i.second._abilityName << " " << i.second._ability << std::endl;
		}
	}
	
	std::string _species;
	std::map<std::string, BodyPart> _body;
	std::vector<std::string> _keys;
	bool _dead;
};