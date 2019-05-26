#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "Slot.h"
#include "Cell.h"
#include "Board.h"
#include "SceneManager.h"

class Game
{
public:
	Game(Board* board, SceneManager* sceneManager);
	void Setup();
	
	GamePhase GetGamePhase();
	void SetGamePhase(GamePhase phase);
	Player GetWinState();
	Player GetSlotOwner(Slot* slot);
	Slot* GetSlotFromPosition(int x, int y);
	Slot* GetSlotFromCell(Cell* cell);
	bool HasHorizontalMatch(Player player);
	bool HasVerticalMatch(Player player);
	bool HasMove(Player player);
	bool IsNeighbour(Slot* slot, Slot* otherSlot);
	bool IsSlotOnGrid(Slot* slot);
	bool IsInitialSlotsEmpty();
	
	void MoveFigure(Slot* sourceSlot, Slot* destinationSlot);
	void RemoveFigure(Slot* slot);
	void UpdateMatches(Player player);

	std::vector<Slot*> GetVerticalMatch(Player player);
	std::vector<Slot*> GetHorizontalMatch(Player player);

private:
	void FindVerticalMatch(Slot* slot, std::vector<Slot*>* match, int dept, Player player);
	void FindHorizontalMatch(Slot* slot, std::vector<Slot*>* match, int dept, Player player);
	void DeactivateSlot(Slot* slot);

	Board* _board = nullptr;
	SceneManager* _sceneManager = nullptr;

	std::map<Slot*, Cell*> _cellMap;
	std::vector<Slot*> _slots;
	GamePhase _gamePhase = GamePhase::PLACING;
};