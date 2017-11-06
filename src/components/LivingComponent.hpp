#pragma once
#include "../level/Item.hpp"
#include <string>
#include <map>

struct BodyPart
{
	std::string _name;
	int _hp;
	std::string _abilityName;
	bool _ability;
	bool _bleeding;
};

struct LivingComponent
{
	LivingComponent() {}
	~LivingComponent() {}
	void handleDamage(Weapon& weapon)
	{

	}
	
	std::string _species;
	std::map<std::string, BodyPart> _body;
	bool _dead;
};