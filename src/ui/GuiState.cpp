#include "GuiState.hpp"
#include "../level/Level.hpp"
#include "../utils/Config.hpp"
#include <algorithm>
#include <iostream>

void DefaultState::update(Gui & gui)
{
	auto bkg = TCODConsole::root->getBackgroundFlag();
	TCODConsole::root->printEx(config.screenWidth - 2, 10, bkg, TCOD_RIGHT, "%s", level._player->_renderer->_name);
	auto body = level._player->_body;
	for (int i = 0; i < body->_parts.size(); i++) {
		auto part = body->_parts[i];
		std::string info = part._name;
		if (!part._ability)
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkestRed, TCODColor::black);
		else if (part._bleeding)
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkRed, TCODColor::black);
		else if (part._hp < data._bodyParts[part._name]._hp)
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::yellow, TCODColor::black);
		else
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
		TCODConsole::root->printEx(config.screenWidth - 2, 12 + i, bkg, TCOD_RIGHT, "%c %s %c", TCOD_COLCTRL_1, info.c_str(), TCOD_COLCTRL_STOP);
	}
	TCODConsole::root->printEx(config.screenWidth - 2, 13 + static_cast<int>(body->_parts.size()), TCOD_BKGND_NONE, TCOD_RIGHT, "%s", level._player->_inventory->_held._name);
}


void LookingTerrain::update(Gui & gui)
{
	DefaultState::update(gui);
	auto terrain = level._terrain[_target._x][_target._y];
	std::map<char, std::string> infos;
	infos['a'] = terrain._renderer->_name;
	if (terrain._actor != nullptr)
		infos['b'] = terrain._actor->_renderer->_name;

	TCODConsole::root->print(1, 10, "%c - %s", 'a', terrain._renderer->_name.c_str());
	if (terrain._actor != nullptr)
		TCODConsole::root->print(1, 11, "%c - %s", 'b', terrain._actor->_renderer->_name.c_str());
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
	transit<DefaultState>(gui);
}

void InspectingTerrain::update(Gui & gui)
{
	DefaultState::update(gui);
	auto terrain = level._terrain[_target._x][_target._y];
	std::map<char, std::string> infos;
	infos['a'] = terrain._renderer->_name;
	if (terrain._actor != nullptr)
		infos['b'] = terrain._actor->_renderer->_name;

	TCODConsole::root->print(1, 10, "This is %s", infos[_choice].c_str());
	if (terrain._actor != nullptr) {
		if (terrain._actor->_renderer->_name == infos[_choice]) {
			auto body = terrain._actor->_body;
			for (int i = 0; i < body->_parts.size(); i++) {
				auto part = body->_parts[i];
				std::string info = part._name;
				if (!part._ability)
					TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkestRed, TCODColor::black);
				else if (part._bleeding)
					TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkRed, TCODColor::black);
				else if (part._hp < data._bodyParts[part._name]._hp)
					TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::yellow, TCODColor::black);
				else
					TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
				TCODConsole::root->print(1, 12 + i, "%c %s %c", TCOD_COLCTRL_1, info.c_str(), TCOD_COLCTRL_STOP);
			}
			TCODConsole::root->print(1, 13 + static_cast<int>(body->_parts.size()), "Holding a %s", terrain._actor->_inventory->_held._name);
		}
	}
}

void InspectingTerrain::exit(Gui & gui)
{
	transit<DefaultState>(gui);
}


void AimTarget::update(Gui & gui)
{
	DefaultState::update(gui);
	std::map<char, std::string> parts;
	for (int i = 0; i < _target._body->_parts.size(); i++)
		parts['a' + i] = _target._body->_parts[i]._name;

	TCODConsole::root->print(1, 10, "Select target:");
	TCODConsole::root->print(1, 11, "a - %s", _target._renderer->_name.c_str());
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
	transit<DefaultState>(gui);
}

void AimPart::update(Gui & gui)
{
	DefaultState::update(gui);
	std::map<char, std::string> parts;
	for (int i = 0; i < _target._body->_parts.size(); i++)
		parts['a' + i] = _target._body->_parts[i]._name;

	TCODConsole::root->print(1, 10, "Select target:");
	for (int i = 0; i < _target._body->_parts.size(); i++) {
		if (!_target._body->_parts[i]._ability)
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkestRed, TCODColor::black);
		else if (_target._body->_parts[i]._bleeding)
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::darkRed, TCODColor::black);
		else
			TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
		TCODConsole::root->print(1, 11 + i, "%c - %c%s%c", 'a' + i, TCOD_COLCTRL_1, parts['a' + i].c_str(), TCOD_COLCTRL_STOP);
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
	transit<DefaultState>(gui);
}

void AimRound::update(Gui & gui)
{
	DefaultState::update(gui);
	gui._attackSelect._bullets = std::max(std::min(gui._attackSelect._bullets, _mag), 1);
	TCODConsole::root->print(1, 10, "Rounds to shoot:");
	TCODConsole::root->print(1, 11, "%d - +/-", gui._attackSelect._bullets);
	TCODConsole::root->print(1, 12, "Press Enter to shoot");
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
	transit<DefaultState>(gui);
}
