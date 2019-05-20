#include "Board.h"
#include "CellData.h"

Board::Board()
{

}

void Board::addSlot(Slot* slot)
{
	_slots.push_back(slot);
}