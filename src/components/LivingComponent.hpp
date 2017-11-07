#pragma once
#include "../level/Item.hpp"
#include "../utils/Global.hpp"
#include "../utils/EventManager.hpp"
#include <string>
#include <memory>
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
	LivingComponent();
	~LivingComponent();

	void init(std::shared_ptr<CommandedSystem> system);
	void update();
	void handleDamage(Weapon& weapon, BodyPart& target, int bullet);
	void bodyInfo();

	std::string _species;
	std::map<std::string, int> _keys;
	std::vector<BodyPart> _body;
	bool _dead;
	std::weak_ptr<CommandedSystem> _system;
};