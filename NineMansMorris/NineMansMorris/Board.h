#pragma once

#include <vector>

#include "Cell.h"

class Board
{
public:
	Board();

	void AddCell(Cell* cell);
	Cell* GetCell(int index);

private:
	std::vector<Cell*> _cells;
};