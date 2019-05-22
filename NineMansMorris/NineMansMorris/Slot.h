#pragma once
#include "Figure.h"

class Slot
{
public:
	Slot(int x, int y);
	~Slot();

	void SetFigure(Figure* figure);
	Figure* GetFigure();
	void UpdateFigurePosition();
	bool IsPointInRect(int x, int y);

private:
	int _positionX = 0;
	int _positionY = 0;
	int _width = 48;
	int _height = 48;
	Figure* _figure = nullptr;
};