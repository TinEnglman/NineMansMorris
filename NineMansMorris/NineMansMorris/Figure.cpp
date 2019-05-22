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
	_figureImageBox->SetPosition(x, y); // todo add animator
}

void Figure::Resize(int w, int h)
{
	_figureImageBox->SetSize(w, h); // todo add animator
}