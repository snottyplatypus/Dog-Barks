#pragma once
#include <memory>

struct ActorSystem;

struct Terrain {

	Terrain() {}
	~Terrain() {}

	char tile_;
	bool isTransparent_;
	bool isWalkable_;
	std::shared_ptr<ActorSystem> actor;
};