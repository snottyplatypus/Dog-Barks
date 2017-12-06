#include "Gui.hpp"
#include "../utils/Global.hpp"
#include "../level/Level.hpp"
#include "../utils/DataManager.hpp"
#include <iostream>
#include <map>
#include <algorithm>

Gui::Gui()
{
	_state = std::make_unique<NothingState>();
}

Gui::~Gui()
{
}

void Gui::update()
{
	//std::cout << _state->_id;
	_state->update(*this);
}
