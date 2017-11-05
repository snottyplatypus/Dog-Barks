#pragma once
#include <string>
#include <map>

struct BodyPart
{
	std::string _name;
	int _hp;
	std::string _abilityName;
	bool _ability;
	bool _bleeding;
};

struct LivingComponent
{
	LivingComponent() {}
	~LivingComponent() {}
	
	std::string _specie;
	std::map<std::string, BodyPart> _body;
};