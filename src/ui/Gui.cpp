#include "Gui.hpp"
#include "../utils/Global.hpp"
#include "../level/Level.hpp"
#include <iostream>
#include <map>
#include <algorithm>

Gui::Gui() : _state(NOTHING_SPECIAL)
{
	_attackSelect = std::make_shared<AttackSelection>();
}

Gui::~Gui()
{
}

void Gui::lookingInfo(std::vector<std::string> info)
{
	for (int i = 0; i < info.size(); i++)
		TCODConsole::root->print(0, 10 + i, "%c - %s", 'a' + i, info[i].c_str());
}

void Gui::attackMenu(CommandedSystem& origin, CommandedSystem& target)
{
	std::map<char, std::string> parts;
	for (int i = 0; i < target._body->_body.size(); i++)
		parts['a' + i] = target._body->_body[i]._name;

	if (_state == START_MENU) {
		_choice = 0;
		_state = SELECTING_TARGET;
	}

	switch (_state) {
	case SELECTING_TARGET:
		TCODConsole::root->print(0, 10, "Select target:");
		TCODConsole::root->print(0, 11, "a - %s", target._renderer->_name.c_str());
		if (_choice == 'a') {
			_attackSelect->_name = target._renderer->_name;
			_choice = 0;
			_state = SELECTING_BODYPART;
		}
		break;
	case SELECTING_BODYPART:
		TCODConsole::root->print(0, 10, "Select target:");
		for (int i = 0; i < target._body->_body.size(); i++)
			TCODConsole::root->print(0, 11 + i, "%c - %s", 'a' + i, parts['a' + i].c_str());
		if (parts.find(_choice) != parts.end()) {
			_attackSelect->_bodyPart = parts[_choice];
			_choice = 0;
			_state = SELECTING_BULLETS;
		}
		break;
	case SELECTING_BULLETS:
		_attackSelect->_bullets = std::max(std::min(_attackSelect->_bullets, origin._inventory->_held._mag), 1);
		TCODConsole::root->print(0, 10, "Rounds to shoot:");
		TCODConsole::root->print(0, 11, "%d - +/-", _attackSelect->_bullets);
		if (_choice == '+') {
			_attackSelect->_bullets++;
			_choice = 0;
		}
		if (_choice == '-') {
			_attackSelect->_bullets--;
			_choice = 0;
		}
		if (_choice == 1) {
			eventManager.onNotify(TRIGGER_ENTER, origin);
			_choice = 0;
		}
		break;
	}
}
