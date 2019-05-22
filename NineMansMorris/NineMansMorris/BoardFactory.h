#pragma once

#include "Board.h"

class BoardFactory
{
	BoardFactory();
	~BoardFactory();

public:
	Board* CreateBoard();

private:
	const int NUM_SLOTS = 24;
	CellData* _cellData;
};
