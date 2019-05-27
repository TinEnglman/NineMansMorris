#include <array>
#include <iostream>

#include "SceneManager.h"
#include "ImageBox.h"


SceneManager::SceneManager(ViewFactory* viewFactory, Animator* animator) :
	_viewFactory(viewFactory), _animator(animator)
{
}

void SceneManager::Draw()
{
	for (unsigned int i = 0; i < _viewBoxes.size(); i++)
	{
		_viewBoxes[i]->Draw();
	}
}

void SceneManager::AddViewBox(ViewBox* viewBox)
{
	_viewBoxes.push_back(viewBox);
}
void SceneManager::RemoveViewBox(ViewBox* viewBox)
{
	int index = 0;
	for (unsigned int i = 0; i < _viewBoxes.size(); i++)
	{
		if (_viewBoxes[i] == viewBox)
		{
			index = i;
			break;
		}
	}
	_viewBoxes.erase(_viewBoxes.begin() + index);
}

Slot* SceneManager::GetInitialSlot(unsigned int index)
{
	if (index < 0 || index >= _initialSlots.size())
	{
		std::cerr << "Initial slot index out of range. \n";
	}

	return _initialSlots[index];
}

Slot* SceneManager::GetBoardSlot(unsigned int index)
{
	if (index < 0 || index >= _boardSlots.size())
	{
		std::cerr << "Initial slot index out of range. \n";
	}

	return _boardSlots[index];
}

int SceneManager::GetNumInitialSlots()
{
	return _initialSlots.size();
}

int SceneManager::GetNumBoardlSlots()
{
	return _boardSlots.size();
}

void SceneManager::SetupInitialSlots()
{
	const int NUM_ROWS = 3;
	const int SEPARATION_X = 60;
	const int SEPARATION_Y = 60;

	for (int i = 0; i < NUM_FIGURES / NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_FIGURES / NUM_ROWS; j++)
		{
			Figure* figure = CreateWhiteFigure();
			CreateInitialSlot(10 + SEPARATION_X * i, 70 + SEPARATION_Y * j, figure);
		}
	}

	for (int i = 0; i < NUM_FIGURES / NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_FIGURES / NUM_ROWS; j++)
		{
			Figure* figure = CreateBlackFigure();
			CreateInitialSlot(590 + SEPARATION_X * i, 70 + SEPARATION_Y * j, figure);
		}
	}
}

void SceneManager::SetupBoardSlots()
{
	std::array<int, NUM_SLOTS> slotPositionsX
	{
		76, 360, 644,
		172, 360, 550,
		265, 360, 455,
		76, 172, 265, 455, 550, 644,
		265, 360, 455,
		172, 360, 550,
		76, 360, 644
	};
	std::array<int, NUM_SLOTS> slotPositionsY
	{
		330, 330, 330,
		424, 424, 424,
		520, 520, 520,
		614, 614, 614, 614, 614, 614,
		706, 706, 706,
		800, 800, 800,
		898, 898, 898
	};

	for (int i = 0; i < NUM_SLOTS; i++)
	{
		CreateBoardSlot(slotPositionsX[i], slotPositionsY[i]);
	}
}

void SceneManager::Reset()
{
	for (Slot* slot : _initialSlots)
	{
		delete slot;
	}
	_initialSlots.clear();

	for (Slot* slot : _boardSlots)
	{
		delete slot;
	}
	_boardSlots.clear();
}

void SceneManager::SetPlayerLabelText(std::string text)
{
	_currentPlayerLabel->SetText(text);
}

void SceneManager::SetPhaseLabelText(std::string text)
{
	_currentPhaseLabel->SetText(text);
}

std::string SceneManager::GetPhaseLabelText()
{
	return _currentPhaseLabel->GetText();
}

void SceneManager::SetTurnLabelText(std::string text)
{
	_turnLabel->SetText(text);
}

void SceneManager::SetTitleLabelText(std::string text)
{
	_titleLabel->SetText(text);
}

void SceneManager::SetupBackground()
{
	auto background = _viewFactory->CreateImageBox(0, 256, 768, 768, "background.png");
	AddViewBox((ViewBox*)background);

	auto topPannel = _viewFactory->CreateImageBox(0, 0, 768, 256, "top_pannel.png");
	AddViewBox((ViewBox*)topPannel);
}

void SceneManager::SetupGUI()
{
	auto playerLabel1 = _viewFactory->CreateTextBox(10, 10, 400, 100, "PLAYER 1");
	playerLabel1->SetColor(255, 255, 0);
	AddViewBox((ViewBox*)playerLabel1);

	auto playerLabel2 = _viewFactory->CreateTextBox(564, 10, 400, 100, "PLAYER 2");
	playerLabel2->SetColor(255, 255, 0);
	AddViewBox((ViewBox*)playerLabel2);

	_turnLabel = _viewFactory->CreateTextBox(340, 15, 400, 100, "TURN");
	_turnLabel->SetColor(225, 155, 0);
	AddViewBox((ViewBox*)_turnLabel);

	_currentPlayerLabel = _viewFactory->CreateTextBox(300, 65, 400, 100, "PLAYER 1");
	_currentPlayerLabel->SetColor(255, 255, 0);
	AddViewBox((ViewBox*)_currentPlayerLabel);

	_titleLabel = _viewFactory->CreateTextBox(340, 140, 400, 100, "PHASE");
	_titleLabel->SetColor(225, 155, 0);
	AddViewBox((ViewBox*)_titleLabel);

	_currentPhaseLabel = _viewFactory->CreateTextBox(310, 190, 400, 100, "PLACING");
	_currentPhaseLabel->SetColor(255, 255, 0);
	AddViewBox((ViewBox*)_currentPhaseLabel);
}

Figure* SceneManager::CreateWhiteFigure()
{
	auto whitePiece = _viewFactory->CreateImageBox(0, 0, FIGURE_WIDTH, FIGURE_HEIGHT, "white_figure.png");
	AddViewBox((ViewBox*)whitePiece);
	
	Figure* figure = new Figure(PLAYER_1_INDEX);
	figure->SetImageBox(whitePiece);
	figure->SetOwner(Player::PLAYER1);
	figure->SetAnimator(_animator);

	return figure;
}

Figure* SceneManager::CreateBlackFigure()
{
	auto blackPiece = _viewFactory->CreateImageBox(0, 0, FIGURE_WIDTH, FIGURE_HEIGHT, "black_figure.png");
	AddViewBox((ViewBox*)blackPiece);

	Figure* figure = new Figure(PLAYER_2_INDEX);
	figure->SetImageBox(blackPiece);
	figure->SetOwner(Player::PLAYER2);
	figure->SetAnimator(_animator);

	return figure;
}

void SceneManager::CreateInitialSlot(int x, int y, Figure* figure)
{
	Slot* slot = new Slot(x, y);
	slot->SetFigure(figure);
	slot->UpdateFigurePosition();
	_initialSlots.push_back(slot);
}


void SceneManager::CreateBoardSlot(int x, int y)
{
	Slot* slot = new Slot(x, y);
	_boardSlots.push_back(slot);
}