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

private:
	int _positionX = 0;
	int _positionY = 0;
	Figure* _figure = nullptr;
};