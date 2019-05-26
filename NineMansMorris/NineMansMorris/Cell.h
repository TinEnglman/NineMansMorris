#pragma once
#include <vector>
#include "Global.h"

class Cell
{
public:
	Cell();
	void AddNeighbour(Cell* cell);
	std::vector<Cell*> GetNeighbours();

	void SetOwner(Player owner);
	Player GetOwner();

private:
	std::vector<Cell*> _neighbours;
	Player _owner = Player::NONE;
};