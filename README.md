# Puzzle solver

An algorithm designed in C++ to solve this kind of puzzles:
https://en.wikipedia.org/wiki/15_puzzle

## Implementation

This algorithm uses STL containers and A* for best possible efficency. The manhattan distance is used as the heuristic function, and the puzzle is considered solved when the tiles are arranged ascendant.

## Input

n - A number representing the puzzle size.
n * n numbers from 0 to n^2-1 representing the puzzle tiles. 0 is considered the empty tile.
