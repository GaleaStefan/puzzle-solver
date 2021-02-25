#pragma once
#include "State.h"

struct ArrayHasher
{
	std::size_t operator()(const State& state) const;
};