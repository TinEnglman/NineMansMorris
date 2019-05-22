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
	delete[] _cellData;
}

Board* BoardFactory::CreateBoard()
{
	Board* board = new Board();
	
	for (int i = 0; i < NUM_SLOTS; i++)
	{
		Cell* cell = new Cell();
		board->AddCell(cell);
	}

	for (int i = 0; i < NUM_SLOTS; i++)
	{
		Cell* cell = board->GetCell(i);
		for (std::vector<int> neighbours : _cellData->_cellData)
		{
			for (int index : neighbours)
			{
				Cell* neighbourCell = board->GetCell(index);
				cell->AddNeighbour(neighbourCell);
			}
		}
	}

	return board;
}