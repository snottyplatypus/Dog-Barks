#pragma once
#include <string>
#include <map>

struct BodyPart
{
	std::string _name;
	int _hp;
	bool _ability;
	bool _bleeding;
};

struct LivingComponent
{
	LivingComponent() {}
	~LivingComponent() {}
	
	std::map<std::string, BodyPart> _body;
};