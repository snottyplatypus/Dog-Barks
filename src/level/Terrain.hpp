#pragma once
#include <memory>

struct ActorSystem;

struct Terrain {

	Terrain(): isTransparent_(true), isWalkable_(true), actor_(nullptr) {}
	~Terrain() {}

	char tile_ = 'X';
	bool isTransparent_;
	bool isWalkable_;
	std::shared_ptr<ActorSystem> actor_;
};