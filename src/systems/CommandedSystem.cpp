#include "CommandedSystem.hpp"


CommandedSystem::CommandedSystem(int x, int y, std::string tile, std::string name, Faction faction) 
	: _updated(false), _faction(faction)
{
	_id = "actor";
	_pos = std::make_shared<PositionComponent>();
	_renderer = std::make_shared<RenderComponent>();
	_move = nullptr;
	_interaction = nullptr;
	_pos->_x = x;
	_pos->_y = y;
	_renderer->_tile = tile;
	_renderer->_name = name;
	_inventory = std::make_shared<InventoryComponent>();
	_body = std::make_shared<LivingComponent>(data._species["human"]);
	_inventory->_held = data._weapons["shotgun"];
	_computing = std::make_shared<ComputingMap>();
	_ai = std::make_shared<AiComponent>();
}

CommandedSystem::~CommandedSystem()
{
}

void CommandedSystem::init(int width, int height)
{
	_body->init(shared_from_this());
	_computing->init(width, height);
}

void CommandedSystem::update()
{
	_body->update();
	if (!_body->_dead) {
		_computing->_map->computeFov(_pos->_x, _pos->_y, _computing->_radius, true, FOV_SHADOW);
		_ai->update(*this);
	}
	else
		_updated = true;
}

void CommandedSystem::command()
{
	if (_move != nullptr) {
		_move->execute(*this);
		_move = nullptr;
		_updated = true;
		eventManager.onNotify(std::make_unique<EndTurn>(), *this);
	}
	if (_interaction != nullptr) {
		_updated = true;
		_interaction->execute(*this);
		_interaction = nullptr;
	}
	if (_body->_dead && _id != "player")
		eventManager.onNotify(std::make_unique<EndTurn>(), *this);
}
