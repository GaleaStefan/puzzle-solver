#include "Node.h"

Node::Node() : state(State(0, std::vector<int>(0))), action(0), parent(NULL), cost(0), level(0)
{

}

Node::Node(State state, Node* parent, int action) : state(state), parent(parent), action(action)
{
	if (parent == NULL)
	{
		level = 0;
	}
	else
	{
		level = parent->level + 1;
	}

	cost = state.mDistance + level;
}

std::string Node::toString()
{
	const static std::string values[] = { "None", "UP", "DOWN", "LEFT", "RIGHT" };
	std::string string = "Node {" + state.toString() + ", Action:" + values[action] + ", cost:" + std::to_string(cost) + "}";

	return string;
}

bool Node::operator<(const Node& node2) const
{
	return !(cost <= node2.cost);
}