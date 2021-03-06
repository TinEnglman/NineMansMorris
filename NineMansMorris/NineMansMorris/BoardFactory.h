#pragma once

#include "Board.h"
#include "CellData.h"

class BoardFactory
{
public:
	BoardFactory();
	~BoardFactory();

	Board* CreateBoard();

private:
	const unsigned int NUM_SLOTS = 24;
	CellData* _cellData;
};
