#include "Figure.h"

Figure::Figure(int playerIndex) : 
	_playerIndex(playerIndex)
{
	
}

void Figure::SetImageBox(ImageBox* imageBox)
{
	_figureImageBox = imageBox;
}

void Figure::MoveTo(int x, int y)
{
	_figureImageBox->SetPosition(x, y);
}