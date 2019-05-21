#include "BoardFactory.h"
#include "Board.h"
#include "Slot.h"

Board* BoardFactory::CreateBoard()
{
	Board* board = new Board();
	
	for (int i = 0; i < NUM_SLOTS; i++)
	{
		//Slot *slot = new Slot();
		//board->AddSlot(slot);
	}

	return board;
}