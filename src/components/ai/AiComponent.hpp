#pragma once
#include <memory>

class AiState;
struct CommandedSystem;

class AiComponent
{
public:
	AiComponent();
	~AiComponent();
	void update(CommandedSystem & system);

	std::unique_ptr<AiState> _state;
};

