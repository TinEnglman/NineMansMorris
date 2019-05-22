#pragma once

#include "Board.h"
#include "MouseController.h"
#include "Slot.h"

class GameController
{
	GameController(Board* board, MouseController* mouseController);

private:
	Board* _board;
	MouseController* _mouseController;
};
