#pragma once
#include "../components/Item.hpp"
#include <map>

class DataManager
{

public:
	DataManager();
	~DataManager();
	void init();

	std::map<std::string, Weapon> _weapons;
};

extern DataManager dataManager;