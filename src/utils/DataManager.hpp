#pragma once
#include "../components/Item.hpp"
#include "Config.hpp"
#include <map>


class DataManager
{

public:
	DataManager();
	~DataManager();
	void init();

	std::map<std::string, Weapon> _weapons;
	
	std::string  font;
};

extern DataManager dataManager;