#pragma once

#include <vector>

#include "ViewFactory.h"
#include "Figure.h"
#include "Slot.h"
#include "Animator.h"

class SceneManager
{
public:
	SceneManager(ViewFactory* viewFactory, Animator* animator);
	void Draw();
	void AddViewBox(ViewBox* viewBox);
	void RemoveViewBox(ViewBox* viewBox);
	Slot* GetInitialSlot(unsigned int index);
	Slot* GetBoardSlot(unsigned int index);
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
	void Reset();

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
	Animator* _animator = nullptr;
};