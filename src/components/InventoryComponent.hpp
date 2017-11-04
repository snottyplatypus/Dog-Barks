#pragma once
#include "../level/Item.hpp"

struct InventoryComponent
{
	InventoryComponent() {}
	~InventoryComponent() {}

	Weapon _held;
};