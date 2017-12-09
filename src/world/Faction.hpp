#pragma once
#include <string>
#include <map>

struct Faction
{
	Faction() 
	{
		_name = "None";
		_relations["default"] = "neutral";
	}
	~Faction() {}

	std::string _name;
	std::map<std::string, std::string> _relations;
};