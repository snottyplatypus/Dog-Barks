#pragma once
#include <memory>
#include <string>
#include "../utils/Command.hpp"
#include "../utils/EventManager.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/RenderComponent.hpp"
#include "../components/InventoryComponent.hpp"
#include "../components/LivingComponent.hpp"
#include "../components/ComputingMapComponent.hpp"
#include "../components/ai/AiComponent.hpp"
#include "../world/Faction.hpp"
#include "../utils/DataManager.hpp"
#include <iostream>
#include <string>

struct CommandedSystem : public std::enable_shared_from_this<CommandedSystem>
{
	CommandedSystem(int x = 1, int y = 1, std::string tile = "gang_b", std::string name = "actor", Faction faction = Faction());
	~CommandedSystem();
	void init(int width, int height);
	void update();
	void command();

	std::string _id;
	std::shared_ptr<PositionComponent> _pos;
	std::shared_ptr<RenderComponent> _renderer;
	std::shared_ptr<InventoryComponent> _inventory;
	std::shared_ptr<LivingComponent> _body;
	std::shared_ptr<Command<CommandedSystem>> _move;
	std::shared_ptr<Command<CommandedSystem>> _interaction;
	std::shared_ptr<ComputingMap> _computing;
	std::shared_ptr<AiComponent> _ai;
	Faction _faction;
	bool _updated;
};
