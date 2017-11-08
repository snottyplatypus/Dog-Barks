#pragma once
#include "../include/libtcod/libtcod.hpp"
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
};

struct Selection
{
};

struct AttackSelection : public Selection
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
	void lookingInfo(std::vector<std::string> info);
	void attackMenu(CommandedSystem& origin, CommandedSystem &target);

	GuiState _state;
	int _choice;
	std::shared_ptr<AttackSelection> _attackSelect;
};

extern Gui gui;