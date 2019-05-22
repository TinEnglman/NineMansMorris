#pragma once
#include <vector>

class Cell
{
public:
	Cell();
	void AddNeighbour(Cell* cell);
	std::vector<Cell*>* GetNeighbours();
private:
	std::vector<Cell*> _neighbours;
};