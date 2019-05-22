#pragma once

#include <vector>

#include "ViewFactory.h"
#include "Figure.h"
#include "Slot.h"

class SceneManager
{
public:
	SceneManager(ViewFactory* viewFactory);
	void Draw();
	void SetupInitialSlots();
	void SetupBackground();
	void SetupGUI();
	void SetupBoardSlots();
	
	void AddViewBox(ViewBox* viewBox);


private:
	Figure* CreateWhiteFigure();
	Figure* CreateBlackFigure();
	void CreateInitialSlot(int x, int y, Figure* figure);
	void CreateBoardSlot(int x, int y);

	std::vector<ViewBox*> _viewBoxes;
	std::vector<Slot*> _initalSlots;
	std::vector<Slot*> _boardSlots;
	ViewFactory* _viewFactory = nullptr;
};