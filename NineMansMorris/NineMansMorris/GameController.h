#pragma once

#include <iostream>
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

private:
	void SelectSlot(Slot *slot);
	void DeselectSlot();
	void MoveFigure(Slot* sorceSlot, Slot* destinationSlot);
	Slot* GetSlotUnderPointer();
	void OnPointerPressed();
	void OnPointerReleased();
	void HandleSelectionPressed();
	void HandleSelectionReleased();
	void UpdateGameState();

	Player GetSlotOwner(Slot* slot);
	std::vector<Slot*> GetVerticalMatch();
	std::vector<Slot*> GetHorizontalMatch();

	void FindVerticalMatch(Slot* slot, std::vector<Slot*>* match, int dept);
	void FindHorizontalMatch(Slot* slot, std::vector<Slot*>* match, int dept);

	Slot* GetSlotFromCell(Cell* cell);

	
	Board* _board = nullptr;
	MouseController* _mouseController = nullptr;
	SceneManager* _sceneManager = nullptr;
	Slot* _selectedSlot = nullptr;
	Slot* _selectionCandidateSlot = nullptr;

	std::map<Slot*, Cell*> _cellMap;
	std::vector<Slot*> _slots;

	Player _currentPlayer = Player::PLAYER1;
	GamePhase _gamePhase = GamePhase::PLACING;
};
