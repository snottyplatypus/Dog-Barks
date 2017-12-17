#include "Line.hpp"
#include "../level/Level.hpp"
#include "DataManager.hpp"

bool PhysicalLine::putPoint(int x, int y)
{
	_lastPos = { x, y };
	switch (TCODConsole::root->getChar(x, y))
	{
	case TCOD_CHAR_BLOCK3:
	case 256:
	case 259:
	case 262:
	case 265:
	case '/':
		return false;
		break;
	default:
		break;
	}	
	TCODConsole::root->putCharEx(x, y, TCODConsole::root->getChar(x, y), TCODConsole::root->getCharForeground(x, y), _bg);
	return true;
}

bool BloodLine::putPoint(int x, int y)
{
	switch (TCODConsole::root->getChar(x + _mod._x, y + _mod._y))
	{
	case TCOD_CHAR_BLOCK3:
	case 256:
	case 259:
	case 262:
	case 265:
	case '/':
		return false;
		break;
	default:
		break;
	}
	if (x > 0 && y > 0 && x < level._width && y < level._height) {
		level._terrain[x][y] = {
								level._terrain[x][y]._renderer->_tile,
								level._terrain[x][y]._renderer->_name,
								level._terrain[x][y]._isTransparent,
								level._terrain[x][y]._isWalkable,
								TCODColor::darkerRed,
								TCODColor::darkestRed
		};
	}
	return true;
}
