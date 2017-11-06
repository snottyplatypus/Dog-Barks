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
	Weapon() : _name("Nothing"), _canDestroyWall(false), _mag(1), _projectiles(1) {};
	~Weapon() {};
	std::string _name;
	bool _canDestroyWall;
	int _mag;
	int _projectiles;
	int _damage;
};
