#include "Cell.h"

Cell::Cell()
{
}

void Cell::AddNeighbour(Cell* cell)
{
	_neighbours.push_back(cell);
}

std::vector<Cell*> Cell::GetNeighbours()
{
	return _neighbours;
}

void  Cell::SetOwner(Player owner)
{
	_owner = owner;
}

Player Cell::GetOwner()
{
	return  _owner;
}