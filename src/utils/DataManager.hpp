#pragma once
#include "../level/Item.hpp"
#include "../components/LivingComponent.hpp"
#include "Config.hpp"
#include <map>


class DataManager
{

public:
	DataManager();
	~DataManager();
	void init();

	std::map<std::string, Weapon> _weapons;
	std::map<std::string, Bodypart> _bodyParts;

	std::string  font;
};

extern DataManager dataManager;