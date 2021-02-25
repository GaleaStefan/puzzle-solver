#pragma once

#include "State.h"

struct Node
{
	// enum actiune

	int level;
	int cost;

	int action;

	Node* parent;
	State state;

	Node();
	Node(State state, Node* parent, int action);
	//~Node(); (completeaza, egal, constructor copiere)

	std::string toString();

	bool operator<(const Node& node2) const;
};