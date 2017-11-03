#pragma once
#include <string>

struct Item
{
	Item() : _name("Nothing") {};
	~Item() {};
	std::string _name;
};

struct Weapon
{
	Weapon() : _name("Nothing"), _canDestroyWall(false) {};
	~Weapon() {};
	std::string _name;
	bool _canDestroyWall;
};
