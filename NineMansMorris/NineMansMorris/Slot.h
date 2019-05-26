#pragma once

#include <vector>
#include <map>

#include "Figure.h"
#include "Global.h"


class Slot
{
public:
	Slot(int x, int y);
	~Slot();

	void SetFigure(Figure* figure);
	Figure* GetFigure();
	void UpdateFigurePosition();
	bool IsPointInRect(int x, int y);
	int GetPositionX();
	int GetPositionY();
	
	void Activate(std::vector<Slot*> activeSlots, Direction direction);
	void Deactivate(Direction direction);
	bool IsActive(Direction direction);

private:
	void ClearActivity(Direction direction);

	int _positionX = 0;
	int _positionY = 0;
	int _width = FIGURE_WIDTH;
	int _height = FIGURE_HEIGHT;
	Figure* _figure = nullptr;
	std::map<Direction, std::vector<Slot*>> _linkedActiveSlots;
};