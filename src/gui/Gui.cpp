#include "Gui.hpp"
#include "../utils/Global.hpp"
#include "../level/Level.hpp"
#include <iostream>

Gui::Gui()
{
}

Gui::~Gui()
{
}

void Gui::lookingInfo(std::vector<std::string> info)
{
	for (int i = 0; i < info.size(); i++)
		TCODConsole::root->print(0, 10 + i, "%c - %s", 'a' + i, info[i].c_str());
}
