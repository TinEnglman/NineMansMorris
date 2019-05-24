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
		_cellMap[boardSlot] = cell;
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
	
	if (_cellMap.find(sourceSlot) != _cellMap.end())
	{
		_cellMap[sourceSlot]->SetOwner(Player::NONE);
	}

	if (_cellMap.find(destinationSlot) != _cellMap.end())
	{
		_cellMap[destinationSlot]->SetOwner(destinationSlot->GetFigure()->GetOwner());
	}

	
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
	HandleSelectionPressed();
}

void GameController::OnPointerReleased()
{
	HandleSelectionReleased();

	std::vector<Slot*> verticalMatch = GetVerticalMatch();
	std::vector<Slot*> horizontalMatch = GetHorizontalMatch();

	if (verticalMatch.size() > 0)
	{
	}

	if (horizontalMatch.size() > 0)
	{
	}
}

void GameController::HandleSelectionPressed()
{
	_selectionCandidateSlot = GetSlotUnderPointer();

	if (_selectionCandidateSlot != nullptr)
	{
		Figure* figure = _selectionCandidateSlot->GetFigure();
		if (figure != nullptr)
		{
			bool isOppositePlayer = figure->GetOwner() != _currentPlayer;
			bool isSelectionOnBoard = _gamePhase == GamePhase::PLACING;
			bool isPlacingPhase = _cellMap.find(_selectionCandidateSlot) != _cellMap.end();
			if (isOppositePlayer || isPlacingPhase && isSelectionOnBoard)
			{
				_selectionCandidateSlot = nullptr;
			}
		}
	}
}

void GameController::HandleSelectionReleased()
{
	Slot* releasedSlot = GetSlotUnderPointer();

	if (releasedSlot != nullptr)
	{
		if (releasedSlot == _selectedSlot && _selectedSlot != nullptr)
		{
			DeselectSlot();
		}
		else if (releasedSlot == _selectionCandidateSlot && releasedSlot->GetFigure() != nullptr)
		{
			if (_selectedSlot != nullptr)
			{
				DeselectSlot();
			}

			SelectSlot(releasedSlot);
		}

		if (_selectedSlot != nullptr)
		{
			bool isTargerSlotEmpty = releasedSlot->GetFigure() == nullptr;
			bool isSelectedSlotFull = _selectedSlot->GetFigure() != nullptr;
			bool isTargetSlotOnGrid = _cellMap.find(releasedSlot) != _cellMap.end();
			bool isPlacingPhase = _gamePhase == GamePhase::PLACING;
			bool isMovingPhase = _gamePhase == GamePhase::MOVING;
			bool isTargetNeighbour = IsNeighbour(_selectedSlot, releasedSlot);
				
			if (isTargerSlotEmpty && isSelectedSlotFull && isTargetSlotOnGrid && (isPlacingPhase || isMovingPhase && isTargetNeighbour))
			{
				Slot* sourceSlot = _selectedSlot;
				DeselectSlot();
				MoveFigure(sourceSlot, releasedSlot);
				UpdateGameState();
			}
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

void GameController::UpdateGameState()
{
	if (_currentPlayer == Player::PLAYER1)
	{
		_currentPlayer = Player::PLAYER2;
		_sceneManager->SetPlayerLabelText("PLAYER 2");
	}
	else
	{
		_currentPlayer = Player::PLAYER1;
		_sceneManager->SetPlayerLabelText("PLAYER 1");
	}
	
	if (_gamePhase == GamePhase::PLACING)
	{
		if (IsInitialSlotsEmpty())
		{
			_gamePhase = GamePhase::MOVING;
			_sceneManager->SetPhaseLabelText("MOVING");
		}
	}

	Player winState = GetWinState();
	if (winState != Player::NONE)
	{
		if (winState == Player::PLAYER1)
		{
			_sceneManager->SetTitleLabelText("PLAYER 1");
			_sceneManager->SetPhaseLabelText("WINNER");
		}
		
		if (winState == Player::PLAYER2)
		{
			_sceneManager->SetTitleLabelText("PLAYER 2");
			_sceneManager->SetPhaseLabelText("WINNER");
		}
	}
}

bool GameController::IsNeighbour(Slot* slot, Slot* otherSlot)
{
	if (_cellMap.find(slot) == _cellMap.end())
	{
		return false;
	}
	
	bool isNeighbour = false;
	for (Cell* cell : _cellMap[slot]->GetNeighbours())
	{
		if (GetSlotFromCell(cell) == otherSlot)
		{
			return true;
		}
	}
	return isNeighbour;
}

Player GameController::GetSlotOwner(Slot* slot)
{
	Cell* cell = _cellMap[slot];
	return cell->GetOwner();
}

std::vector<Slot*> GameController::GetVerticalMatch()
{
	for (std::pair<Slot*, Cell*> pair : _cellMap)
	{
		Slot* slot = pair.first;
		Cell* cell = pair.second;
		
		if (cell->GetOwner() != Player::NONE)
		{
			std::vector<Slot*> matchingSlots;
			matchingSlots.push_back(slot);
			
			FindVerticalMatch(slot, &matchingSlots, 3);

			if (matchingSlots.size() == 3)
			{
				return matchingSlots;
			}
		}
	}

	return std::vector<Slot*>();
}
std::vector<Slot*> GameController::GetHorizontalMatch()
{

	for (std::pair<Slot*, Cell*> pair : _cellMap)
	{
		Slot* slot = pair.first;
		Cell* cell = pair.second;

		if (cell->GetOwner() != Player::NONE)
		{
			std::vector<Slot*> matchingSlots;
			matchingSlots.push_back(slot);

			FindHorizontalMatch(slot, &matchingSlots, 3);

			if (matchingSlots.size() == 3)
			{
				return matchingSlots;
			}
		}
	}

	return std::vector<Slot*>();
}

void GameController::FindVerticalMatch(Slot* slot, std::vector<Slot*>* match, int dept)
{
	if (dept == 1)
	{
		return;
	}
	
	Player slotOwner = _cellMap[slot]->GetOwner();
	std::vector<Cell*> neighbours = _cellMap[slot]->GetNeighbours();

	for (Cell* candidateCell : neighbours)
	{
		Slot* candidateSlot = GetSlotFromCell(candidateCell);
		Player candidateOwner = candidateCell->GetOwner();

		if (candidateSlot->GetPositionX() == slot->GetPositionX() && candidateSlot->GetPositionY() > slot->GetPositionY() && candidateOwner == slotOwner)
		{
			match->push_back(candidateSlot);
			FindVerticalMatch(candidateSlot, match, dept - 1);
		}
	}
}

void GameController::FindHorizontalMatch(Slot* slot, std::vector<Slot*>* match, int dept)
{
	if (dept == 1)
	{
		return;
	}

	Player slotOwner = _cellMap[slot]->GetOwner();
	std::vector<Cell*> neighbours = _cellMap[slot]->GetNeighbours();

	for (Cell* candidateCell : neighbours)
	{
		Slot* candidateSlot = GetSlotFromCell(candidateCell);
		Player candidateOwner = candidateCell->GetOwner();

		if (candidateSlot->GetPositionY() == slot->GetPositionY() && candidateSlot->GetPositionX() > slot->GetPositionX() && candidateOwner == slotOwner)
		{
			match->push_back(candidateSlot);
			FindHorizontalMatch(candidateSlot, match, dept - 1);
		}
	}
}

Slot* GameController::GetSlotFromCell(Cell* cell)
{
	for (Slot* slot : _slots)
	{
		if (_cellMap[slot] == cell)
		{
			return slot;
		}
	}

	std::cerr << "No matching slot found for cell. \n";
	return nullptr;
}

bool GameController::IsInitialSlotsEmpty()
{
	bool isEmpty = true;
	for (Slot* slot : _slots)
	{
		if (_cellMap.find(slot) == _cellMap.end())
		{
			if (slot->GetFigure() != nullptr)
			{
				return false;
			}
		}
	}
	
	return isEmpty;
}

Player GameController::GetWinState()
{
	Player winState = Player::NONE;
	
	int numPlayer1Figures = 0;
	int numPlayer2Figures = 0;
	for (Slot* slot : _slots)
	{
		if (_cellMap.find(slot) != _cellMap.end())
		{
			if (slot->GetFigure() != nullptr)
			{
				if (slot->GetFigure()->GetOwner() == Player::PLAYER1)
				{
					numPlayer1Figures++;
				}

				if (slot->GetFigure()->GetOwner() == Player::PLAYER2)
				{
					numPlayer2Figures++;
				}
			}
		}
	}

	if (numPlayer1Figures < 3 &&  _gamePhase != GamePhase::PLACING)
	{
		winState = Player::PLAYER2;
	}
	else if (numPlayer2Figures < 3 && _gamePhase != GamePhase::PLACING)
	{
		winState = Player::PLAYER1;
	}
	
	return winState;
}