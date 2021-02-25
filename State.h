#pragma once

#include <vector>
#include <string>

struct State
{
	int gridSize;
	int mDistance;

	std::vector<int> tiles;

	State();
	State(int gridSize, std::vector<int> tiles);
	State(const State& previous, int emptyMoveDirection);

	bool isGoalState() const;

	void calculateManhattanDistance();
	int calculateInversions() const;

	int getEmptyTileIndex() const;

	std::string toString() const;

	bool operator==(const State& state2) const;
	//bool operator<(const State& other) const;
};