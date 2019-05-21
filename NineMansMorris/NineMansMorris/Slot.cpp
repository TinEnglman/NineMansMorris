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