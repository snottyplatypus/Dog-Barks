#include "DataManager.hpp"
#include <libtcod/libtcod.hpp>
#include <yaml-cpp/yaml.h>
#include "../systems/CommandedSystem.hpp"
#include "../world/Faction.hpp"
#include <iostream>

DataManager::DataManager()
{
	_tiles["nothing"] = ' ';
	_tiles["ground"] = '.';
	_tiles["grass1"] = ',';
	_tiles["grass2"] = ';';
	_tiles["grass3"] = '"';
	_tiles["floor"] = '+';
	_tiles["block1"] = TCOD_CHAR_BLOCK1;
	_tiles["block2"] = TCOD_CHAR_BLOCK2;
	_tiles["block3"] = TCOD_CHAR_BLOCK3;
	_tiles["door"] = '/';
	_tiles["cursor"] = 'X';
	_tiles["civilian"] = 256;
	_tiles["civilian dead"] = 257;
	_tiles["gang_a"] = 259;
	_tiles["gang_a_dead"] = 260;
	_tiles["gang_b"] = 262;
	_tiles["gang_b_dead"] = 263;
	_tiles["swat"] = 265;
	_tiles["swat_dead"] = 266;

	_factions["None"];
	_weapons["Nothing"];
	_player = std::make_shared<CommandedSystem>();
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

	file = YAML::LoadFile("data/living/player.yaml");
	_player->_inventory->_held = _weapons[file["PLAYER"]["weapon"].as<std::string>()];
	*_player->_body = _species[file["PLAYER"]["species"].as<std::string>()];
	_player->_renderer->_tile = file["PLAYER"]["tile"].as<std::string>();
	_player->_renderer->_name = "you";
	_player->_faction = _factions[file["PLAYER"]["faction"].as<std::string>()];
}
