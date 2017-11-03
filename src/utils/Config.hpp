#pragma once
#include <string>

struct Config
{
	int screenWidth;
	int screenHeight;
	std::string font;
};

extern Config config;