#pragma once
#include "../level/Item.hpp"
#include "../components/LivingComponent.hpp"
#include "Config.hpp"
#include <memory>
#include <map>

struct CommandedSystem;
struct Faction;

class DataManager
{

public:
	DataManager();
	~DataManager();
	void init();
	 
	std::map<std::string, int> _tiles;
	std::map<std::string, Weapon> _weapons;
	std::vector<std::string> _wKeys;
	std::map<std::string, BodyPart> _bodyParts;
	std::map<std::string, LivingComponent> _species;
	std::map<std::string, CommandedSystem> _actors;
	std::map<std::string, Faction> _factions;
	std::shared_ptr<CommandedSystem> _player;

	std::string  font;
};

extern DataManager data;