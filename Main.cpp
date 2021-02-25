#include "Solver.h"


int main()
{
	std::ifstream in("in.txt");
	std::ofstream out("out.txt");

	int size;
	in >> size;

	Solver solver(size, in, out);
	solver.solvePuzzle();
}