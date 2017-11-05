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
	std::map<std::string, BodyPart> _bodyParts;
	std::map<std::string, LivingComponent> _species;

	std::string  font;
};

extern DataManager dataManager;