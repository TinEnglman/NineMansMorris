#pragma once

#include "Board.h"
#include "CellData.h"

class BoardFactory
{
	BoardFactory();

public:
	Board* CreateBoard();

private:
	const int NUM_SLOTS = 24;
};
