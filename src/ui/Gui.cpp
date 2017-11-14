#include "Gui.hpp"
#include "../utils/Global.hpp"
#include "../level/Level.hpp"
#include "../utils/DataManager.hpp"
#include <iostream>
#include <map>
#include <algorithm>

Gui::Gui() : _state(NOTHING_SPECIAL)
{
}

Gui::~Gui()
{
}

void Gui::lookingInfo(PositionComponent target)
{
	if (_state == START_MENU) {
		_choice = 0;
		_state = SELECTING_TARGET;
	}

	auto terrain = level._terrain[target._x][target._y];
	std::map<char, std::string> infos;
	infos['a'] = terrain._renderer->_name;
	if (terrain._actor != nullptr)
		infos['b'] = terrain._actor->_renderer->_name;
	switch (_state) {
	case SELECTING_TARGET:
		TCODConsole::root->print(0, 10, "%c - %s", 'a', terrain._renderer->_name.c_str());
		if (terrain._actor != nullptr)
			TCODConsole::root->print(0, 11, "%c - %s", 'b', terrain._actor->_renderer->_name.c_str());
		if (infos.find(_choice) != infos.end()) {
			_state = INSPECTING;
		}
		break;
	case INSPECTING:
		TCODConsole::root->print(0, 10, "This is %s", infos[_choice].c_str());
		if (terrain._actor != nullptr) {
			if (terrain._actor->_renderer->_name == infos[_choice]) {
				auto body = terrain._actor->_body;
				for (int i = 0; i < body->_body.size(); i++) {
					auto part = body->_body[i];
					std::string info = part._name;
					if (!part._ability)
						TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkestRed, TCODColor::black);
					else if (part._bleeding)
						TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkRed, TCODColor::black);
					else
						TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
					TCODConsole::root->print(0, 12 + i, "%c %s %c", TCOD_COLCTRL_1, info.c_str(), TCOD_COLCTRL_STOP);
				}
			}
		}
		break;
	}
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
			_attackSelect._name = target._renderer->_name;
			_choice = 0;
			_state = SELECTING_BODYPART;
		}
		break;
	case SELECTING_BODYPART:
		TCODConsole::root->print(0, 10, "Select target:");
		for (int i = 0; i < target._body->_body.size(); i++) {
			if (!target._body->_body[i]._ability)
				TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkestRed, TCODColor::black);
			else if (target._body->_body[i]._bleeding)
				TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkRed, TCODColor::black);
			else
				TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
			TCODConsole::root->print(0, 11 + i, "%c - %c%s%c", 'a' + i, TCOD_COLCTRL_1, parts['a' + i].c_str(), TCOD_COLCTRL_STOP);
		}
		if (parts.find(_choice) != parts.end()) {
			_attackSelect._bodyPart = parts[_choice];
			_choice = 0;
			_state = SELECTING_BULLETS;
		}
		break;
	case SELECTING_BULLETS:
		_attackSelect._bullets = std::max(std::min(_attackSelect._bullets, origin._inventory->_held._mag), 1);
		TCODConsole::root->print(0, 10, "Rounds to shoot:");
		TCODConsole::root->print(0, 11, "%d - +/-", _attackSelect._bullets);
		TCODConsole::root->print(0, 12, "Press Enter to shoot");
		if (_choice == '+') {
			_attackSelect._bullets++;
			_choice = 0;
		}
		if (_choice == '-') {
			_attackSelect._bullets--;
			_choice = 0;
		}
		if (_choice == 1) {
			eventManager.onNotify(TRIGGER_ENTER, origin);
			_choice = 0;
		}
		break;
	}
}
