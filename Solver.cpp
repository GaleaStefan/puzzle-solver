#include "Solver.h"
#include <iostream>

Solver::Solver(int size, std::istream& inFile, std::ostream& outFile) : gridSize(size), inFile(inFile), outFile(outFile)
{
	
}

std::vector<int> Solver::readInitialConfiguration()
{
	std::vector<int> startConfig(gridSize * gridSize);

	for (int i = 0; i < gridSize * gridSize; i++)
	{
		inFile >> startConfig[i];
	}

	return startConfig;
}

bool Solver::isSolvable(State config)
{
	int inversions = config.calculateInversions();
	int emptyPosition = config.getEmptyTileIndex();
	int emptyRow = (gridSize - emptyPosition / gridSize + 1);
	bool oddRow = emptyRow % 2 == 1;

	if ((gridSize % 2 == 1 && inversions % 2 == 0) || (gridSize % 2 == 0 && oddRow == (inversions % 2 == 0)))
	{
		return true;
	}

	return false;
}

void Solver::generateChild(Node parent, State state, int action)
{
	Node child(state, new Node(parent), action);
	open.push(child);
}

void Solver::generateChildren(Node parent)
{
	int emptyIndex = parent.state.getEmptyTileIndex();
	std::pair<int, int> emptyPos(emptyIndex / gridSize, emptyIndex % gridSize);

	if (emptyPos.first > 0 && parent.action != 2)
	{
		State up(parent.state, 1); // UP

		if (explored.find(up) == explored.end()) // evita duplicate
		{
			//std::cout << up.toString() << std::endl;
			generateChild(parent, up, 1);
		}
	}

	if (emptyPos.first < gridSize - 1 && parent.action != 1)
	{
		State down(parent.state, 2); // DOWN

		if (explored.find(down) == explored.end()) // evita duplicate
		{
			//std::cout << down.toString() << std::endl;
			generateChild(parent, down, 2);
		}
	}

	if (emptyPos.second > 0 && parent.action != 4)
	{
		State left(parent.state, 3); // LEFT

		if (explored.find(left) == explored.end()) // evita duplicate
		{
			//std::cout << left.toString() << std::endl;
			generateChild(parent, left, 3);
		}
	}

	if (emptyPos.second < gridSize - 1 && parent.action != 3)
	{
		State right(parent.state, 4); // RIGHT

		if (explored.find(right) == explored.end()) // evita duplicate
		{
			//std::cout << right.toString() << std::endl;
			generateChild(parent, right, 4);
		}
	}

}

void Solver::solvePuzzle()
{
	State startState(gridSize, readInitialConfiguration());

	if (!isSolvable(startState))
	{
		outFile << "Nu se poate rezolva";
		return;
	}

	Node first(startState, NULL, 0);
	open.push(first);

	while (true)
	{
		if (open.empty())
		{
			return;
		}

		Node currentNode(open.top());
		//std::cout << currentNode.toString() << std::endl;
		open.pop();

		if (currentNode.state.isGoalState() == true)
		{
			goal = currentNode;
			printSolution();
			return;
		}

		generateChildren(currentNode);
	}
}

void Solver::printSolution()
{
	std::vector<Node*> nodes;
	

	Node* current = &goal;
	nodes.push_back(current);
	
	while (current->parent)
	{
		nodes.push_back(current->parent);
		current = current->parent;
	}

	outFile << "Mutari necesare:" << nodes.size() << std::endl << std::endl;

	for (int i = nodes.size() - 1; i >= 0; i--)
	{
		outFile << nodes[i]->toString() << std::endl;
	}
}