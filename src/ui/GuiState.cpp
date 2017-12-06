#include "GuiState.hpp"
#include "../level/Level.hpp"
#include <algorithm>
#include <iostream>

void LookingTerrain::update(Gui & gui)
{
	auto terrain = level._terrain[_target._x][_target._y];
	std::map<char, std::string> infos;
	infos['a'] = terrain._renderer->_name;
	if (terrain._actor != nullptr)
		infos['b'] = terrain._actor->_renderer->_name;

	TCODConsole::root->print(0, 10, "%c - %s", 'a', terrain._renderer->_name.c_str());
	if (terrain._actor != nullptr)
		TCODConsole::root->print(0, 11, "%c - %s", 'b', terrain._actor->_renderer->_name.c_str());
	if (infos.find(gui._choice) != infos.end()) {
		next(gui);
		gui._choice = 0;
	}
}

void LookingTerrain::next(Gui & gui)
{
	gui._state = std::make_unique<InspectingTerrain>(_target, gui._choice);
}

void LookingTerrain::exit(Gui & gui)
{
	transit<NothingState>(gui);
}

void InspectingTerrain::update(Gui & gui)
{
	auto terrain = level._terrain[_target._x][_target._y];
	std::map<char, std::string> infos;
	infos['a'] = terrain._renderer->_name;
	if (terrain._actor != nullptr)
		infos['b'] = terrain._actor->_renderer->_name;

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
				else if (part._hp < data._bodyParts[part._name]._hp)
					TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::yellow, TCODColor::black);
				else
					TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
				TCODConsole::root->print(0, 12 + i, "%c %s %c", TCOD_COLCTRL_1, info.c_str(), TCOD_COLCTRL_STOP);
			}
		}
	}
}

void InspectingTerrain::exit(Gui & gui)
{
	transit<NothingState>(gui);
}


void AimTarget::update(Gui & gui)
{
	std::map<char, std::string> parts;
	for (int i = 0; i < _target._body->_body.size(); i++)
		parts['a' + i] = _target._body->_body[i]._name;

	TCODConsole::root->print(0, 10, "Select target:");
	TCODConsole::root->print(0, 11, "a - %s", _target._renderer->_name.c_str());
	if (gui._choice == 'a') {
		gui._attackSelect._name = _target._renderer->_name;
		gui._choice = 0;
		next(gui);
	}
	else
		exit(gui);
}

void AimTarget::next(Gui & gui)
{
	gui._state = std::make_unique<AimPart>(_target, _mag);
}

void AimTarget::exit(Gui & gui)
{
	transit<NothingState>(gui);
}

void AimPart::update(Gui & gui)
{
	std::map<char, std::string> parts;
	for (int i = 0; i < _target._body->_body.size(); i++)
		parts['a' + i] = _target._body->_body[i]._name;

	TCODConsole::root->print(0, 10, "Select target:");
	for (int i = 0; i < _target._body->_body.size(); i++) {
		if (!_target._body->_body[i]._ability)
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkestRed, TCODColor::black);
		else if (_target._body->_body[i]._bleeding)
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkRed, TCODColor::black);
		else
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
		TCODConsole::root->print(0, 11 + i, "%c - %c%s%c", 'a' + i, TCOD_COLCTRL_1, parts['a' + i].c_str(), TCOD_COLCTRL_STOP);
	}
	if (parts.find(gui._choice) != parts.end()) {
		gui._attackSelect._bodyPart = parts[gui._choice];
		gui._choice = 0;
		next(gui);
	}
}

void AimPart::next(Gui & gui)
{
	gui._state = std::make_unique<AimRound>(_target, _mag);
}

void AimPart::exit(Gui & gui)
{
	transit<NothingState>(gui);
}

void AimRound::update(Gui & gui)
{
	gui._attackSelect._bullets = std::max(std::min(gui._attackSelect._bullets, _mag), 1);
	TCODConsole::root->print(0, 10, "Rounds to shoot:");
	TCODConsole::root->print(0, 11, "%d - +/-", gui._attackSelect._bullets);
	TCODConsole::root->print(0, 12, "Press Enter to shoot");
	if (gui._choice == '+') {
		gui._attackSelect._bullets++;
		gui._choice = 0;
	}
	if (gui._choice == '-') {
		gui._attackSelect._bullets--;
		gui._choice = 0;
	}
}

void AimRound::next(Gui & gui)
{
	exit(gui);
}

void AimRound::exit(Gui & gui)
{
	transit<NothingState>(gui);
}
