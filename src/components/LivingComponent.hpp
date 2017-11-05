#pragma once
#include <string>
#include <map>

struct BodyPart
{
	std::string name;
	int hp;
	bool ability;
	bool bleeding;
};

struct LivingComponent
{
	LivingComponent() {}
	LivingComponent() {}
	
	std::map<std::string, BodyPart> _body;
};