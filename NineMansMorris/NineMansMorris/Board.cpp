#include <iostream>

#include "Board.h"
#include "CellData.h"

Board::Board()
{
}

void Board::AddCell(Cell* cell)
{
	_cells.push_back(cell);
}

Cell* Board::GetCell(unsigned int index)
{
	if (index < 0 || index > _cells.size())
	{
		std::cerr << "Cell index out of range.\n";
	}
	return _cells[index];
}

int Board::GetNumCells()
{
	return _cells.size();
}
