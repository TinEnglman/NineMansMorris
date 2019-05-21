#include "Board.h"
#include "CellData.h"

Board::Board()
{

}

void Board::AddSlot(Slot* slot)
{
	_slots.push_back(slot);
}