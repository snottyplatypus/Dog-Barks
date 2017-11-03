#include "DataManager.hpp"
#include "../include/yaml-cpp/yaml.h"
#include <iostream>

DataManager::DataManager()
{
	_weapons["Nothing"];
}

DataManager::~DataManager()
{
}

void DataManager::init()
{
	YAML::Node configFile = YAML::LoadFile("data/config.yaml");
	config.screenWidth = configFile["width"].as<int>();
	config.screenHeight = configFile["height"].as<int>();
	config.font = configFile["font"].as<std::string>();

	YAML::Node weapons = YAML::LoadFile("data/item/item_weapon.yaml");
	for (std::size_t i = 0; i < weapons.size(); i++) {
		std::string name = weapons[i]["name"].as<std::string>();
		_weapons[name]._name = weapons[i]["name"].as<std::string>();
		_weapons[name]._canDestroyWall = weapons[i]["canDestroyWall"];
	}
}
