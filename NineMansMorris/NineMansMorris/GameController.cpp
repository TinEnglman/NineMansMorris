#include "GameController.h"

GameController::GameController(Board* board, MouseController* mouseController, SceneManager* sceneManager) :
	_board(board), _mouseController(mouseController), _sceneManager(sceneManager)
{
}

void GameController::Setup()
{
	for (int i = 0; i < _board->GetNumCells(); i++)
	{
		Slot* slot = _sceneManager->GetBoardSlot(i);
		Cell* cell = _board->GetCell(i);
		_cellMap[cell] = slot;
	}
}