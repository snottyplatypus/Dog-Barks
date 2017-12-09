#pragma once
#include <memory>
#include "AiState.hpp"

class AiComponent
{
public:
	AiComponent();
	~AiComponent();
	void update(CommandedSystem & system);

	std::unique_ptr<AiState> _state;
};

