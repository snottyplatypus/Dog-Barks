#pragma once
#include "../include/libtcod/libtcod.hpp"

extern TCODRandom rng;
extern TCOD_key_t key;

static const int MIN_ROOM_SIZE = 2 + 2;
static const int MAX_ROOM_SIZE = 7 + 2;
static const int DISTANCE_BORDERS = 4;

static const int SCREEN_WIDTH = 80;
static const int SCREEN_HEIGHT = 50;