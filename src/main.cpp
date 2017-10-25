#include "include/libtcod/libtcod.hpp"
#include "utils/Global.hpp"
#include "level/Level.hpp"
#include "utils/EventManager.hpp"
#include "utils/InputHandler.hpp"
#include "gui/Gui.hpp"
#include <iostream>

TCODRandom rng;
TCOD_key_t key;
Level level;
Gui gui;
InputHandler inputHandler;
EventManager eventManager;

int main()
{
	TCODConsole::setCustomFont("../assets/font10x10.png", TCOD_FONT_LAYOUT_ASCII_INROW, 16, 16);
	TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "Dog Barks");
	while (!TCODConsole::isWindowClosed())
	{
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr);
		TCODConsole::root->clear();
		level.update();
		TCODConsole::root->flush();
	}
	return 0;
}
