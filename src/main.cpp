#include <sstream>
#include "include/libtcod/libtcod.hpp"
#include "systems/PlayerSystem.hpp"
#include "level/Level.hpp"
#include "utils/EventManager.hpp"

Level level;
EventManager eventManager;

int main()
{
	TCODConsole::initRoot(80, 50, "Dog Barks");
	while (!TCODConsole::root->isWindowClosed())
	{
		TCODConsole::root->clear();
		level.update();
		TCODConsole::root->flush();
	}
	return 0;
}