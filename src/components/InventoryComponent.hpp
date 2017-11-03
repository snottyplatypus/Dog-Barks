#pragma once
#include "Item.hpp"

struct InventoryComponent
{
	InventoryComponent() {}
	~InventoryComponent() {}

	Weapon _held;
};