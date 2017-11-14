#pragma once
#include "GameObjectSystem.hpp"
#include "../utils/EventManager.hpp"
#include "../components/InventoryComponent.hpp"
#include "../components/LivingComponent.hpp"
#include "../components/ComputingMapComponent.hpp"
#include <iostream>
#include <string>
#include "../utils/DataManager.hpp"

struct CommandedSystem : public GameObjectSystem, public std::enable_shared_from_this<CommandedSystem>
{
	CommandedSystem(int x = 1, int y = 1, std::string tile = "gang_b", std::string name = "actor") : _updated(false)
	{
		_pos->_x = x;
		_pos->_y = y;
		_renderer->_tile = tile;
		_renderer->_name = name;
		_id = "actor";
		_inventory = std::make_shared<InventoryComponent>();
		_body = std::make_shared<LivingComponent>(data._species["human"]);
		_inventory->_held = data._weapons["shotgun"];
		_computing = std::make_shared<ComputingMap>();
	}

	~CommandedSystem() {}

	void init(int width, int height)
	{
		_body->init(shared_from_this());
		_computing->init(width, height);
	}

	void update() 
	{
		_body->update();
		if (!_body->_dead)
			_computing->_map->computeFov(_pos->_x, _pos->_y, _computing->_radius);
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
	std::shared_ptr<ComputingMap> _computing;
	bool _updated;
};
