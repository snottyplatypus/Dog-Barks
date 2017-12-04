#pragma once
#include <libtcod/libtcod.hpp>
#include "../systems/CommandedSystem.hpp"
#include <memory>
#include <vector>
#include <string>

enum GuiState
{
	NOTHING_SPECIAL,
	START_MENU,
	SELECTING_TARGET,
	SELECTING_BODYPART,
	SELECTING_BULLETS,
	INSPECTING,
};

struct AttackSelection
{
	std::string _name = " ";
	std::string _bodyPart = " ";
	int _bullets = 1;
};

class Gui
{
public:
	Gui();
	~Gui();
	void lookingInfo(PositionComponent target);
	void attackMenu(CommandedSystem& origin, CommandedSystem& target);

	int _state;
	int _choice;
	AttackSelection _attackSelect;
};

extern Gui gui;