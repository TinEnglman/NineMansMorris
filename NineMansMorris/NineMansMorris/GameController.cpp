#include "GameController.h"

GameController::GameController(Game* game, MouseController* mouseController, SceneManager* sceneManager) :
	_game(game), _mouseController(mouseController), _sceneManager(sceneManager)
{
}

void GameController::Setup()
{
	std::function< void() > pressedCallback = std::bind(&GameController::OnPointerPressed, this);
	std::function< void() > releasedCallback = std::bind(&GameController::OnPointerReleased, this);

	_mouseController->SetPressedCallback(pressedCallback);
	_mouseController->SetReleasedCallback(releasedCallback);
}

void GameController::SelectSlot(Slot* slot)
{
	_selectedSlot = slot;
	_selectedSlot->GetFigure()->Resize(54, 54); // todo add animation
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
	_game->MoveFigure(sourceSlot, destinationSlot); // todo add animations
	destinationSlot->UpdateFigurePosition();
}

void GameController::RemoveFigure(Slot* sourceSlot)
{
	Figure* targetFigure = sourceSlot->GetFigure();
	_game->RemoveFigure(sourceSlot);
	delete targetFigure;
	sourceSlot->SetFigure(nullptr);
}

Slot* GameController::GetSlotUnderPointer()
{
	int x = _mouseController->GetMousePositionX();
	int y = _mouseController->GetMousePositionY();
	return _game->GetSlotFromPosition(x, y);
}

void GameController::OnPointerPressed()
{
	HandleSelectionPressed();
}

void GameController::OnPointerReleased()
{
	HandleSelectionReleased();
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
			bool isPlacingPhase = _game->GetGamePhase() == GamePhase::PLACING;
			bool isSelectionOnBoard = _game->IsSlotOnGrid(_selectionCandidateSlot);
			bool isRemovingPhase = _game->GetGamePhase() == GamePhase::REMOVING;

			if (isOppositePlayer && !isRemovingPhase || isSelectionOnBoard && isPlacingPhase)
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
			bool isTargetSlotOnGrid = _game->IsSlotOnGrid(releasedSlot);
			bool isPlacingPhase = _game->GetGamePhase() == GamePhase::PLACING;
			bool isMovingPhase = _game->GetGamePhase() == GamePhase::MOVING;
			bool isRemovingPhase = _game->GetGamePhase() == GamePhase::REMOVING;
			bool isTargetNeighbour = _game->IsNeighbour(_selectedSlot, releasedSlot);
				
			if (isTargerSlotEmpty && isSelectedSlotFull && isTargetSlotOnGrid && (isPlacingPhase || isMovingPhase && isTargetNeighbour))
			{
				Slot* sourceSlot = _selectedSlot;
				DeselectSlot();
				MoveFigure(sourceSlot, releasedSlot);
				UpdateMatches(_currentPlayer);
				UpdateGameState();
			}
			else if (isRemovingPhase)
			{
				_sceneManager->RemoveViewBox((ViewBox*)releasedSlot->GetFigure()->GetImageBox());
				RemoveFigure(releasedSlot);
				_game->SetGamePhase(_previousGamePhase);
				_sceneManager->SetPhaseLabelText(_previousPhaseLabelText);
				UpdateGameState();
				_selectedSlot = nullptr;
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
	if (_game->GetGamePhase() != GamePhase::REMOVING)
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
	}
	
	if (_game->GetGamePhase() == GamePhase::PLACING)
	{
		if (_game->IsInitialSlotsEmpty())
		{
			_previousGamePhase = _game->GetGamePhase();
			_previousPhaseLabelText = _sceneManager->GetPhaseLabelText();
			_game->SetGamePhase(GamePhase::MOVING);
			_sceneManager->SetPhaseLabelText("MOVING");
		}
	}

	Player winState = _game->GetWinState();
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

void GameController::UpdateMatches(Player player)
{
	bool hasMatch = _game->HasHorizontalMatch(player) || _game->HasVerticalMatch(player);

	_game->UpdateMatches(player);

	if (hasMatch)
	{
		_game->SetGamePhase(GamePhase::REMOVING);
		_sceneManager->SetPhaseLabelText("REMOVING");
	}
}