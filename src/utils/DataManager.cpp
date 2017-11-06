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
	YAML::Node file = YAML::LoadFile("data/config.yaml");
	config.screenWidth = file["width"].as<int>();
	config.screenHeight = file["height"].as<int>();
	config.font = file["font"].as<std::string>();

	file = YAML::LoadFile("data/item/item_weapon.yaml");
	for (std::size_t i = 0; i < file.size(); i++) {
		std::string name = file[i]["name"].as<std::string>();
		_weapons[name]._name = file[i]["name"].as<std::string>();
		_weapons[name]._canDestroyWall = file[i]["canDestroyWall"].as<bool>();
		_weapons[name]._mag = file[i]["mag"].as<int>();
		_weapons[name]._projectiles = file[i]["projectiles"].as<int>();
		_weapons[name]._damage = file[i]["damage"].as<int>();
	}

	file = YAML::LoadFile("data/living/body_part.yaml");
	for (std::size_t i = 0; i < file.size(); i++) {
		std::string name = file[i]["species"].as<std::string>() + "_" + file[i]["type"].as<std::string>();
		_bodyParts[name]._name = file[i]["type"].as<std::string>();
		_bodyParts[name]._hp = file[i]["hp"].as<int>();
		_bodyParts[name]._abilityName = file[i]["ability"].as<std::string>();
	}
	
	file = YAML::LoadFile("data/living/species.yaml");
	for (std::size_t i = 0; i < file.size(); i++) {
		std::string name = file[i]["name"].as<std::string>();
		_species[name]._species = name;
		for (YAML::const_iterator it = file[i]["parts"].begin(); it != file[i]["parts"].end(); ++it)
			_species[name]._body[it->first.as<std::string>()] = _bodyParts[it->second.as<std::string>()];
	}
}
