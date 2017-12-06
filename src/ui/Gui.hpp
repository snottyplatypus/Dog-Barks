#pragma once
#include <libtcod/libtcod.hpp>
#include "../systems/CommandedSystem.hpp"
#include "GuiState.hpp"
#include <memory>
#include <vector>
#include <string>

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
	void update();

	std::unique_ptr<GuiState> _state;
	int _choice;
	AttackSelection _attackSelect;
};

extern Gui gui;