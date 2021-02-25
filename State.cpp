#include "State.h"
#include <math.h>
#include <utility>

State::State() : gridSize(0)
{

}

State::State(int gridSize, std::vector<int> tiles) : gridSize(gridSize), tiles(tiles)
{
	calculateManhattanDistance();
}

State::State(const State& previous, int moveDirection) : gridSize(previous.gridSize), tiles(previous.tiles)
{
	int emptyIndex = previous.getEmptyTileIndex();

	std::pair<int, int> emptyPos(emptyIndex / gridSize, emptyIndex % gridSize);
	std::pair<int, int> newPos = std::pair<int, int>(emptyPos.first, emptyPos.second);

	switch (moveDirection)
	{
	case 1: //up
		newPos.first -= 1;
		break;
	case 2: //down
		newPos.first += 1;
		break;
	case 3: //left
		newPos.second -= 1;
		break;
	case 4: //right
		newPos.second += 1;
		break;
	default:
		break;
	}

	int newIndex = newPos.first * gridSize + newPos.second;

	int temp = tiles[emptyIndex];
	tiles[emptyIndex] = tiles[newIndex];
	tiles[newIndex] = temp;

	calculateManhattanDistance();
}

bool State::isGoalState() const
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i] != 0 && tiles[i] != i + 1)
		{
			return false;
		}
	}

	return (tiles[gridSize * gridSize - 1] == 0);
}

int State::calculateInversions() const
{
	int inversions = 0;

	for (int i = 0; i < tiles.size(); i++)
	{
		int element = tiles[i];

		for (int j = i + 1; j < tiles.size(); j++)
		{
			if (element > tiles[j])
			{
				inversions++;
			}
		}
	}

	return inversions;
}

void State::calculateManhattanDistance()
{
	mDistance = 0;

	for (int i = 0; i < tiles.size(); i++)
	{
		std::pair<int, int> location(i / gridSize, i % gridSize);
		std::pair<int, int> destination;
		if (tiles[i] == 0)
		{
			destination = std::pair<int, int>(gridSize - 1, gridSize - 1);
		}
		else
		{
			destination = std::pair<int, int>((tiles[i] - 1) / gridSize, (tiles[i] - 1) % gridSize);
		}

		mDistance += (abs(location.first - destination.first) + abs(location.second - destination.second));
	}
}

int State::getEmptyTileIndex() const
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i] == 0)
		{
			return i;
		}
	}
}

std::string State::toString() const
{
	std::string string = "State{";

	for (int i = 0; i < tiles.size() - 1; i++)
	{
		string = string + std::to_string(tiles[i]) + ", ";
	}

	string += std::to_string(tiles[tiles.size() - 1]) + "}" + " Manhattan:" + std::to_string(mDistance) + "}";

	return string;
}

bool State::operator==(const State& state2) const
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i] != state2.tiles[i])
		{
			return false;
		}
	}

	return true;
}