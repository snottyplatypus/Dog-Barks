#pragma once
#include <string>
#include <map>

struct Config
{
	int screenWidth;
	int screenHeight;
	std::string font;
	int MIN_ROOM_SIZE;
	int MAX_ROOM_SIZE;
	int DISTANCE_BORDERS;
	int MAX_ENEMY_PER_ROOM;
	int MIN_OFFICER;
	int MAX_OFFICER;
	std::map<std::string, char> binding;
};

extern Config config;