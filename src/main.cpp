#include "include/libtcod/libtcod.hpp"
#include "utils/Global.hpp"
#include "level/Level.hpp"
#include "utils/EventManager.hpp"
#include "utils/InputHandler.hpp"
#include "utils/DataManager.hpp"
#include "graphics/Gui.hpp"
#include "graphics/Effect.hpp"
#include <iostream>

Config config;
DataManager dataManager;
TCODRandom rng;
TCOD_key_t key;
Level level;
Gui gui;
InputHandler inputHandler;
EventManager eventManager;
float time;

int main()
{
	dataManager.init();
	TCODConsole::setCustomFont(config.font.c_str(), TCOD_FONT_LAYOUT_ASCII_INROW, 16, 16);
	TCODConsole::initRoot(config.screenWidth, config.screenHeight, "Dog Barks");
	TCODSystem::setFps(60);
	level.init();
	while (!TCODConsole::isWindowClosed())
	{
		time += TCODSystem::getLastFrameLength();
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, nullptr);
		TCODConsole::root->clear();
		level.update();
		TCODConsole::root->flush();
	}
	return 0;
}
