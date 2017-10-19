#pragma once
#include "include/libtcod/libtcod.hpp"

enum Tile {
	NOTHING = ' ',
	PLAYER = 1,
	ACTOR = 2,
	FLOOR = '+',
	BLOCK3 = TCOD_CHAR_BLOCK3,
};
