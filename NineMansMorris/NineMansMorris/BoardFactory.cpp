#include "CellData.h"
#include "BoardFactory.h"
#include "Board.h"
#include "Slot.h"

BoardFactory::BoardFactory()
{
	_cellData = new CellData();
}

BoardFactory::~BoardFactory()
{
	delete _cellData;
}

Board* BoardFactory::CreateBoard()
{
	Board* board = new Board();
	
	for (unsigned int i = 0; i < NUM_SLOTS; i++)
	{
		Cell* cell = new Cell();
		board->AddCell(cell);
	}

	for (unsigned int i = 0; i < _cellData->_cellData.size(); i++)
	{
		Cell* cell = board->GetCell(i);
		for (unsigned int index : _cellData->_cellData[i])
		{
			Cell* neighbourCell = board->GetCell(index);
			cell->AddNeighbour(neighbourCell);
		}
	}

	return board;
}