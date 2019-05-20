#pragma once

#include <vector>

#include "Slot.h"

class Board
{
public:
	Board();
	~Board();

	void addSlot(Slot *slot);

private:
	std::vector<Slot*> _slots;
};