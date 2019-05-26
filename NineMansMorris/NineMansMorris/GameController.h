#pragma once

#include <iostream>
#include <map>
#include <functional>

#include "Board.h"
#include "MouseController.h"
#include "Slot.h"
#include "SceneManager.h"
#include "Game.h"

class GameController
{
public:
	GameController(Game* game, MouseController* mouseController, SceneManager* _sceneManager);
	void Setup();

private:
	void SelectSlot(Slot *slot);
	void DeselectSlot();
	void MoveFigure(Slot* sorceSlot, Slot* destinationSlot);
	void RemoveFigure(Slot* slot);
	Slot* GetSlotUnderPointer();
	void OnPointerPressed();
	void OnPointerReleased();
	void HandleSelectionPressed();
	void HandleSelectionReleased();
	void UpdateGameState();
	void UpdateMatches(Player player);

	Game* _game = nullptr;
	MouseController* _mouseController = nullptr;
	SceneManager* _sceneManager = nullptr;
	Slot* _selectedSlot = nullptr;
	Slot* _selectionCandidateSlot = nullptr;

	Player _currentPlayer = Player::PLAYER1;
	GamePhase _previousGamePhase = GamePhase::PLACING;
	std::string _previousPhaseLabelText = "PLACING";
};
