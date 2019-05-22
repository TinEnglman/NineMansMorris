#pragma once
#include <map>

#include "Board.h"
#include "MouseController.h"
#include "Slot.h"
#include "SceneManager.h"

class GameController
{
public:
	GameController(Board* board, MouseController* mouseController, SceneManager* _sceneManager);
	void Setup();

private:
	Board* _board;
	MouseController* _mouseController;
	SceneManager* _sceneManager;

	std::map<Cell*, Slot*> _cellMap;
};
