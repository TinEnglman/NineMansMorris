#pragma once

#include "Board.h"
#include "MouseController.h"

class GameController
{
	GameController(Board* board, MouseController* mouseController);

private:
	Board* _board;
	MouseController* _mouseController;
};
