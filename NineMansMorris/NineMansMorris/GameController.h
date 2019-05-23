#pragma once
#include <map>
#include <functional>

#include "Board.h"
#include "MouseController.h"
#include "Slot.h"
#include "SceneManager.h"

class GameController
{
public:
	GameController(Board* board, MouseController* mouseController, SceneManager* _sceneManager);
	void Setup();
	void Update();

private:
	void SelectSlot(Slot *slot);
	void DeselectSlot();
	void MoveFigure(Slot* sorceSlot, Slot* destinationSlot);
	Slot* GetSlotUnderPointer();
	void OnPointerPressed();
	void OnPointerReleased();
	
	Board* _board = nullptr;
	MouseController* _mouseController = nullptr;
	SceneManager* _sceneManager = nullptr;
	Slot* _selectedSlot = nullptr;
	Slot* _selectionCandidateSlot = nullptr;

	std::map<Cell*, Slot*> _cellMap;
	std::vector<Slot*> _slots;
};
