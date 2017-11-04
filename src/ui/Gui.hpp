#pragma once
#include "../include/libtcod/libtcod.hpp"
#include <memory>
#include <vector>
#include <string>

class Gui
{
public:
	Gui();
	~Gui();
	void lookingInfo(std::vector<std::string> info);

};

extern Gui gui;