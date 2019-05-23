#include "Slot.h"

Slot::Slot(int x, int y) : 
	_positionX(x), _positionY(y)
{
}

Slot::~Slot()
{
	if (_figure != nullptr)
	{
		delete[] _figure;
	}
}

void Slot::SetFigure(Figure* figure)
{
	_figure = figure;
}

Figure* Slot::GetFigure()
{
	return _figure;
}

void Slot::UpdateFigurePosition()
{
	_figure->MoveTo(_positionX, _positionY);
}

bool Slot::IsPointInRect(int x, int y)
{
	if (x >= _positionX && x < (_positionX + _width) && y >= _positionY && y < (_positionY + _height))
	{
		return true;
	}
	return false;
}

int Slot::GetPositionX()
{
	return _positionX;
}
int Slot::GetPositionY()
{
	return _positionY;
}