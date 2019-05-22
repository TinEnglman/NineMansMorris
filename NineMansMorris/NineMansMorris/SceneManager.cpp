#include <array>

#include "SceneManager.h"
#include "ImageBox.h"


SceneManager::SceneManager(ViewFactory* viewFactory) :
	_viewFactory(viewFactory)
{
}

void SceneManager::SetupInitialSlots()
{
	const int NUM_FIGURES = 9;
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
	const int NUM_SLOTS = 24;
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

Figure* SceneManager::CreateWhiteFigure()
{
	auto whitePiece = _viewFactory->CreateImageBox(0, 0, 48, 48, "white_figure.png");
	AddViewBox((ViewBox*)whitePiece);
	
	Figure* figure = new Figure(0);
	figure->SetImageBox(whitePiece);

	return figure;
}


Figure* SceneManager::CreateBlackFigure()
{
	auto blackPiece = _viewFactory->CreateImageBox(0, 0, 48, 48, "black_figure.png");
	AddViewBox((ViewBox*)blackPiece);

	Figure* figure = new Figure(1);
	figure->SetImageBox(blackPiece);

	return figure;
}

void SceneManager::CreateInitialSlot(int x, int y, Figure* figure)
{
	Slot* slot = new Slot(x, y);
	slot->SetFigure(figure);
	slot->UpdateFigurePosition();
	_initalSlots.push_back(slot);
}


void SceneManager::CreateBoardSlot(int x, int y)
{
	Slot* slot = new Slot(x, y);
	_boardSlots.push_back(slot);
}