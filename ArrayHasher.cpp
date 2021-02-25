#include "ArrayHasher.h"

std::size_t ArrayHasher::operator()(const State& state) const
{
	std::size_t seed = state.tiles.size();

	for (auto& i : state.tiles)
	{
		seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	return seed;
}