#pragma once
#include "../include/libtcod/libtcod.hpp"

enum Tile 
{
	NOTHING = ' ',
	GROUND = '.',
	FLOOR = '+',
	BLOCK1 = TCOD_CHAR_BLOCK1,
	BLOCK2 = TCOD_CHAR_BLOCK2,
	BLOCK3 = TCOD_CHAR_BLOCK3,
	DOOR = '/',
	CURSOR = 'X',
	CIVILIAN = 256,
	CIVILIAN_DEAD = 257,
	GANG_A = 265,
	GANG_A_DEAD = 260,
	GANG_B = 262,
	GANG_B_DEAD = 263,
	POLICEMAN = 267,
	POLICEMAN_DEAD = 266,
};