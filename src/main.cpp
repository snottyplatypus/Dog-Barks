#include <libtcod/libtcod.hpp>
#include "utils/Global.hpp"
#include "level/Level.hpp"
#include "utils/EventManager.hpp"
#include "utils/InputHandler.hpp"
#include "utils/DataManager.hpp"
#include "ui/Gui.hpp"
#include "ui/Effect.hpp"
#include <iostream>

Config config;
DataManager data;
TCODRandom rng;
TCOD_key_t key;
Level level;
Gui gui;
InputHandler inputHandler;
EventManager eventManager;
float time;

int main()
{
	data.init();
	TCODConsole::setCustomFont(config.font.c_str(), TCOD_FONT_LAYOUT_ASCII_INROW, 16, 17);
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
