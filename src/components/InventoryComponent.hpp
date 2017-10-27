#pragma once
enum Item
{
	NOTHING_HELD,
	SHOTGUN,
};
struct InventoryComponent
{
	InventoryComponent() : held(NOTHING_HELD) {}
	~InventoryComponent() {}

	int held;
};