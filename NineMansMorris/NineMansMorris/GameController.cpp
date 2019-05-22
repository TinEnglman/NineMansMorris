#include "GameController.h"

GameController::GameController(Board* board, MouseController* mouseController, SceneManager* sceneManager) :
	_board(board), _mouseController(mouseController), _sceneManager(sceneManager)
{
}

void GameController::Setup()
{
	for (int i = 0; i < _board->GetNumCells(); i++)
	{
		Slot* boardSlot = _sceneManager->GetBoardSlot(i);
		Cell* cell = _board->GetCell(i);
		_cellMap[cell] = boardSlot;
		_slots.push_back(boardSlot);
	}

	for (int i = 0; i < _sceneManager->GetNumInitialSlots(); i++)
	{
		Slot* initialSlot = _sceneManager->GetInitialSlot(i);
		_slots.push_back(initialSlot);
	}
}

void GameController::Update()
{
	if (_selectedSlot == nullptr)
	{
		if (_mouseController->IsPointerPressed() && _selectionCandidateSlot == nullptr)
		{
			int x = _mouseController->GetMousePositionX();
			int y = _mouseController->GetMousePositionY();
		
			for (Slot* slot : _slots)
			{
				if (slot->IsPointInRect(x, y))
				{
					_selectionCandidateSlot = slot;
					break;
				}
			}
		}

		if (!_mouseController->IsPointerPressed() && _selectionCandidateSlot != nullptr)
		{
			int x = _mouseController->GetMousePositionX();
			int y = _mouseController->GetMousePositionY();

			if (_selectionCandidateSlot->IsPointInRect(x, y))
			{
				_previousSelectedSlot = _selectedSlot;
				_selectedSlot = _selectionCandidateSlot;
				_selectionCandidateSlot = nullptr;
			}
		}
	}

	if (_selectedSlot != nullptr)
	{
		if (_mouseController->IsPointerPressed())
		{
			int x = _mouseController->GetMousePositionX();
			int y = _mouseController->GetMousePositionY();

			for (Slot* slot : _slots)
			{
				if (slot->IsPointInRect(x, y))
				{
					_selectionCandidateSlot = slot;
					break;
				}
			}
		}

		if (!_mouseController->IsPointerPressed() && _selectionCandidateSlot != nullptr)
		{
			int x = _mouseController->GetMousePositionX();
			int y = _mouseController->GetMousePositionY();

			if (_selectionCandidateSlot->IsPointInRect(x, y))
			{
				_previousSelectedSlot = _selectedSlot;
				_selectedSlot = _selectionCandidateSlot;
			}

			if (_selectionCandidateSlot == nullptr)
			{
				_selectedSlot = nullptr;
			}
		}

	}

	if (_selectedSlot != nullptr)
	{
		if (_selectedSlot->GetFigure() != nullptr)
		{
			if (_previousSelectedSlot != nullptr)
			{
				_previousSelectedSlot->GetFigure()->Resize(48, 48);
			}
			_selectedSlot->GetFigure()->Resize(54, 54);
		}
	}
}