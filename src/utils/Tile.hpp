#pragma once
#include "../include/libtcod/libtcod.hpp"

enum Tile {
	NOTHING = ' ',
	PLAYER = 1,
	ACTOR = 2,
	GROUND = '.',
	FLOOR = '+',
	BLOCK1 = TCOD_CHAR_BLOCK1,
	BLOCK2 = TCOD_CHAR_BLOCK2,
	BLOCK3 = TCOD_CHAR_BLOCK3,
	DOOR = '/',
};