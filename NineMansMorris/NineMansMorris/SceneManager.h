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
	void AddViewBox(ViewBox* viewBox);
	Slot* GetInitialSlot(int index);
	Slot* GetBoardSlot(int index);
	int GetNumInitialSlots();
	int GetNumBoardlSlots();
	
	void SetupInitialSlots();
	void SetupBackground();
	void SetupGUI();
	void SetupBoardSlots();

private:
	Figure* CreateWhiteFigure();
	Figure* CreateBlackFigure();
	void CreateInitialSlot(int x, int y, Figure* figure);
	void CreateBoardSlot(int x, int y);

	std::vector<ViewBox*> _viewBoxes;
	std::vector<Slot*> _initialSlots;
	std::vector<Slot*> _boardSlots;
	ViewFactory* _viewFactory = nullptr;
};