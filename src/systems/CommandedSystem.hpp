#pragma once
#include "GameObjectSystem.hpp"
#include "../utils/EventManager.hpp"
#include "../components/InventoryComponent.hpp"
#include "../components/LivingComponent.hpp"
#include <iostream>
#include <string>
#include "../utils/DataManager.hpp"

struct CommandedSystem : public GameObjectSystem, public std::enable_shared_from_this<CommandedSystem>
{
	CommandedSystem(int x = 1, int y = 1, std::string tile = "gang_b", std::string name = "Actor") : _updated(false)
	{
		_pos->_x = x;
		_pos->_y = y;
		_renderer->_tile = tile;
		_renderer->_name = name;
		_id = "actor";
		_inventory = std::make_shared<InventoryComponent>();
		_body = std::make_shared<LivingComponent>(data._species["human"]);
		_inventory->_held = data._weapons["Shotgun"];
	}

	~CommandedSystem() {}

	void init()
	{
		_body->init(shared_from_this());
	}

	void update() 
	{
		_body->update();
	}

	void command()
	{
		if (_move != nullptr) {
			_move->execute(*this);
			_move = nullptr;
			_updated = true;
			eventManager.onNotify(END_TURN, *this);
		}
		if (_interaction != nullptr) {
			_interaction->execute(*this);
			_interaction = nullptr;
			_updated = true;
			eventManager.onNotify(END_TURN, *this);
		}
		// TEMP UNTIL AI
		if (_id != "player") {
			_updated = true;
			eventManager.onNotify(END_TURN, *this);
		}
	}

	std::shared_ptr<InventoryComponent> _inventory;
	std::shared_ptr<LivingComponent> _body;
	std::shared_ptr<Command<CommandedSystem>> _interaction;
	bool _updated;
};
