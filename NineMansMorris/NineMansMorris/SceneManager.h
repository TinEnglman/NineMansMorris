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
	void RemoveViewBox(ViewBox* viewBox);
	Slot* GetInitialSlot(int index);
	Slot* GetBoardSlot(int index);
	int GetNumInitialSlots();
	int GetNumBoardlSlots();
	void SetPlayerLabelText(std::string text);
	void SetPhaseLabelText(std::string text);
	std::string GetPhaseLabelText();
	void SetTurnLabelText(std::string text);
	void SetTitleLabelText(std::string text);

	
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
	TextBox* _currentPlayerLabel = nullptr;
	TextBox* _currentPhaseLabel = nullptr;
	TextBox* _turnLabel = nullptr;
	TextBox* _titleLabel = nullptr;
	ViewFactory* _viewFactory = nullptr;
};