#include "Game.h"

Game::Game(Board* board, SceneManager* sceneManager) :
	_board(board), _sceneManager(sceneManager)
{
}

void Game::Setup()
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
}

GamePhase Game::GetGamePhase()
{
	return _gamePhase;
}

void Game::SetGamePhase(GamePhase phase)
{
	_gamePhase = phase;
}

Player Game::GetWinState()
{
	Player winState = Player::NONE;

	std::map<Player, int> numFigures;
	std::map<Player, bool> hasMoves;
	
	for (Slot* slot : _slots)
	{
		if (_cellMap.find(slot) != _cellMap.end())
		{
			if (slot->GetFigure() != nullptr)
			{
				Player owner = slot->GetFigure()->GetOwner();
				numFigures[owner]++;
			}
		}
	}

	hasMoves[Player::PLAYER1] = HasMove(Player::PLAYER1);
	hasMoves[Player::PLAYER2] = HasMove(Player::PLAYER2);

	if (_gamePhase != GamePhase::PLACING)
	{
		if (numFigures[Player::PLAYER1] < MATCH_SIZE  && _gamePhase != GamePhase::REMOVING || !hasMoves[Player::PLAYER1])
		{
			winState = Player::PLAYER2;
		}
		else if (numFigures[Player::PLAYER2] < MATCH_SIZE && _gamePhase != GamePhase::REMOVING || !hasMoves[Player::PLAYER1])
		{
			winState = Player::PLAYER1;
		}
	}
	return winState;
}

Player Game::GetSlotOwner(Slot* slot)
{
	Cell* cell = _cellMap[slot];
	return cell->GetOwner();
}

Slot* Game::GetSlotFromPosition(int x, int y)
{
	for (Slot* slot : _slots)
	{
		if (slot->IsPointInRect(x, y))
		{
			return slot;
		}
	}
	return nullptr;
}

Slot* Game::GetSlotFromCell(Cell* cell)
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

bool Game::HasHorizontalMatch(Player player)
{
	return GetHorizontalMatch(player).size() >= MATCH_SIZE;
}
bool Game::HasVerticalMatch(Player player)
{
	return GetVerticalMatch(player).size() >= MATCH_SIZE;
}

bool Game::HasMove(Player player)
{
	for (std::pair<Slot*, Cell*> it : _cellMap)
	{
		Slot* slot = it.first;
		Cell* cell = it.second;
		Figure* figure = slot->GetFigure();

		if (figure != nullptr)
		{
			if (figure->GetOwner() == player)
			{
				for (Cell* currentCell : cell->GetNeighbours())
				{
					if (GetSlotFromCell(currentCell)->GetFigure() == nullptr)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

void Game::RemoveFigure(Slot* slot)
{
	Player owner = slot->GetFigure()->GetOwner();
	DeactivateSlot(slot);
}

void Game::MoveFigure(Slot* sourceSlot, Slot* destinationSlot)
{
	DeactivateSlot(sourceSlot);
	DeactivateSlot(destinationSlot);
	
	if (_cellMap.find(sourceSlot) != _cellMap.end())
	{
		_cellMap[sourceSlot]->SetOwner(Player::NONE);
	}

	if (_cellMap.find(destinationSlot) != _cellMap.end())
	{
		_cellMap[destinationSlot]->SetOwner(destinationSlot->GetFigure()->GetOwner());
	}
}

void Game::UpdateMatches(Player player)
{
	std::vector<Slot*> verticalMatch = GetVerticalMatch(player);
	
	if (verticalMatch.size() >= MATCH_SIZE)
	{
		for (Slot* slot : verticalMatch)
		{
			if (!slot->IsActive(Direction::VERTICAL))
			{
				slot->Activate(verticalMatch, Direction::VERTICAL);
			}
		}
	}
	
	std::vector<Slot*> horizontalMatch = GetHorizontalMatch(player);

	if (horizontalMatch.size() >= MATCH_SIZE)
	{
		for (Slot* slot : horizontalMatch)
		{
			if (!slot->IsActive(Direction::HORIZONTAL))
			{
				slot->Activate(horizontalMatch, Direction::HORIZONTAL);
			}
		}
	}
}

bool Game::IsNeighbour(Slot* slot, Slot* otherSlot)
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

bool Game::IsSlotOnGrid(Slot* slot)
{
	return _cellMap.find(slot) != _cellMap.end();
}


bool Game::IsInitialSlotsEmpty()
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

std::vector<Slot*> Game::GetVerticalMatch(Player player)
{
	for (std::pair<Slot*, Cell*> pair : _cellMap)
	{
		Slot* slot = pair.first;
		Cell* cell = pair.second;

		if (cell->GetOwner() == player && !slot->IsActive(Direction::VERTICAL))
		{
			std::vector<Slot*> matchingSlots;
			matchingSlots.push_back(slot);

			FindVerticalMatch(slot, &matchingSlots, MATCH_SIZE, player);

			if (matchingSlots.size() == MATCH_SIZE)
			{
				return matchingSlots;
			}
		}
	}

	return std::vector<Slot*>();
}

std::vector<Slot*> Game::GetHorizontalMatch(Player player)
{
	for (std::pair<Slot*, Cell*> pair : _cellMap)
	{
		Slot* slot = pair.first;
		Cell* cell = pair.second;

		if (cell->GetOwner() == player && !slot->IsActive(Direction::HORIZONTAL))
		{
			std::vector<Slot*> matchingSlots;
			matchingSlots.push_back(slot);

			FindHorizontalMatch(slot, &matchingSlots, MATCH_SIZE, player);

			if (matchingSlots.size() == MATCH_SIZE)
			{
				return matchingSlots;
			}
		}
	}

	return std::vector<Slot*>();
}

void Game::FindVerticalMatch(Slot* slot, std::vector<Slot*>* match, int dept, Player player)
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
			FindVerticalMatch(candidateSlot, match, dept - 1, player);
		}
	}
}

void Game::FindHorizontalMatch(Slot* slot, std::vector<Slot*>* match, int dept, Player player)
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
			FindHorizontalMatch(candidateSlot, match, dept - 1, player);
		}
	}
}

void Game::DeactivateSlot(Slot* slot)
{
	if (slot->IsActive(Direction::VERTICAL))
	{
		slot->Deactivate(Direction::VERTICAL);
	}
	if (slot->IsActive(Direction::HORIZONTAL))
	{
		slot->Deactivate(Direction::HORIZONTAL);
	}
}

