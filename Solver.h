#pragma once
#include "Node.h"

#include <fstream>
#include <map>
#include <queue>
#include <unordered_map>
#include "ArrayHasher.h"

struct Solver
{
	int gridSize;

	// nu au ce cauta fisiere in solver(-> main)
	std::istream& inFile;
	std::ostream& outFile;

	Node goal;

	std::unordered_map<State, Node, ArrayHasher> explored;
	std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type>> open;

	Solver(int size, std::istream& inFile, std::ostream& outFile);

	std::vector<int> readInitialConfiguration();

	void generateChild(Node parent, State state, int action);
	void generateChildren(Node node);

	bool isSolvable(State config);
	void solvePuzzle();
	void printSolution();
};