#include "DataManager.hpp"
#include <libtcod/libtcod.hpp>
#include <yaml-cpp/yaml.h>
#include "../systems/CommandedSystem.hpp"
#include "../world/Faction.hpp"
#include <iostream>

DataManager::DataManager()
{
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
	config.MIN_ROOM_SIZE = file["MIN_ROOM_SIZE"].as<int>();
	config.MAX_ROOM_SIZE = file["MAX_ROOM_SIZE"].as<int>();
	config.DISTANCE_BORDERS = file["DISTANCE_BORDERS"].as<int>();
	config.MAX_ENEMY_PER_ROOM = file["MAX_ENEMY_PER_ROOM"].as<int>();
	config.MIN_OFFICER = file["MIN_OFFICER"].as<int>();
	config.MAX_OFFICER = file["MAX_OFFICER"].as<int>();
	for (YAML::const_iterator it = file["bindings"].begin(); it != file["bindings"].end(); ++it)
		config.binding[it->first.as<std::string>()] = it->second.as<char>();
	for (YAML::const_iterator it = file["tiles"].begin(); it != file["tiles"].end(); ++it)
		_tiles[it->first.as<std::string>()] = it->second.as<int>();

	file = YAML::LoadFile("data/item/item_weapon.yaml");
	for (std::size_t i = 0; i < file.size(); i++) {
		std::string name = file[i]["name"].as<std::string>();
		_weapons[name]._name = file[i]["name"].as<std::string>();
		_weapons[name]._canDestroyWall = file[i]["canDestroyWall"].as<bool>();
		_weapons[name]._mag = file[i]["mag"].as<int>();
		_weapons[name]._projectiles = file[i]["projectiles"].as<int>();
		_weapons[name]._damage = file[i]["damage"].as<int>();
	}
	for (auto i : _weapons)
		_wKeys.push_back(i.first);

	file = YAML::LoadFile("data/living/body_part.yaml");
	for (std::size_t i = 0; i < file.size(); i++) {
		std::string name = file[i]["species"].as<std::string>() + "_" + file[i]["type"].as<std::string>();
		_bodyParts[name]._name = file[i]["type"].as<std::string>();
		_bodyParts[name]._hp = file[i]["hp"].as<int>();
		_bodyParts[name]._abilityName = file[i]["ability"].as<std::string>();
		_bodyParts[name]._ability = true;
		_bodyParts[name]._bleeding = false;
		_bodyParts[name]._shot = false;
	}
	
	file = YAML::LoadFile("data/living/species.yaml");
	for (std::size_t i = 0; i < file.size(); i++) {
		std::string name = file[i]["name"].as<std::string>();
		_species[name]._species = name;
		for (YAML::const_iterator it = file[i]["parts"].begin(); it != file[i]["parts"].end(); ++it) {
			_species[name]._parts.push_back(_bodyParts[it->second.as<std::string>()]);
			_species[name]._parts.back()._name = it->first.as<std::string>();
		}
	}

	file = YAML::LoadFile("data/world/faction.yaml");
	for (std::size_t i = 0; i < file.size(); i++) {
		std::string name = file[i]["name"].as<std::string>();
		_factions[name]._name = name;
		for (auto j = _factions.begin(); j != _factions.end(); ++j)
			for (std::size_t k = 0; k < file.size(); k++)
				if (j->second._name == file[k]["name"].as<std::string>())
					for (YAML::const_iterator it = file[k]["relations"].begin(); it != file[k]["relations"].end(); ++it)
						j->second._relations[it->first.as<std::string>()] = it->second.as<std::string>();
	}

	_player = std::make_shared<CommandedSystem>();
	file = YAML::LoadFile("data/living/player.yaml");
	_player->_inventory->_held = _weapons[file["PLAYER"]["weapon"].as<std::string>()];
	*_player->_body = _species[file["PLAYER"]["species"].as<std::string>()];
	_player->_renderer->_tile = file["PLAYER"]["tile"].as<std::string>();
	_player->_renderer->_name = file["PLAYER"]["name"].as<std::string>();
	_player->_faction = _factions[file["PLAYER"]["faction"].as<std::string>()];
}
