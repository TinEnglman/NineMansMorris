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

	std::function< void() > pressedCallback = std::bind(&GameController::OnPointerPressed, this);
	std::function< void() > releasedCallback = std::bind(&GameController::OnPointerReleased, this);

	_mouseController->SetPressedCallback(pressedCallback);
	_mouseController->SetReleasedCallback(releasedCallback);
}

void GameController::Update()
{
	

}

void GameController::SelectSlot(Slot* slot)
{
	_selectedSlot = slot;
	_selectedSlot->GetFigure()->Resize(54, 54);
}
void GameController::DeselectSlot()
{
	_selectedSlot->GetFigure()->Resize(48, 48);
	_selectedSlot = nullptr;
}

void GameController::MoveFigure(Slot* sourceSlot, Slot* destinationSlot)
{
	destinationSlot->SetFigure(sourceSlot->GetFigure());
	sourceSlot->SetFigure(nullptr);
	
	destinationSlot->UpdateFigurePosition();
}

Slot* GameController::GetSlotUnderPointer()
{
	int x = _mouseController->GetMousePositionX();
	int y = _mouseController->GetMousePositionY();
	for (Slot* slot : _slots)
	{
		if (slot->IsPointInRect(x, y))
		{
			return slot;
		}
	}
	return nullptr;
}

void GameController::OnPointerPressed()
{
	_selectionCandidateSlot = GetSlotUnderPointer();
}

void GameController::OnPointerReleased()
{
	Slot* releasedSlot = GetSlotUnderPointer();
	
	if (releasedSlot != nullptr)
	{
		if (releasedSlot == _selectionCandidateSlot && releasedSlot->GetFigure() != nullptr)
		{
			SelectSlot(releasedSlot);
		}

		if (releasedSlot->GetFigure() == nullptr && _selectedSlot->GetFigure() != nullptr)
		{
			Slot* sourceSlot = _selectedSlot;
			DeselectSlot();
			MoveFigure(sourceSlot, releasedSlot);
		}
	}
	else
	{
		if (_selectionCandidateSlot == nullptr && _selectedSlot != nullptr)
		{
			DeselectSlot();
		}
	}

	_selectionCandidateSlot = nullptr;
}