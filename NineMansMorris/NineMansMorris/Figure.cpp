#include "Figure.h"

Figure::Figure(int playerIndex) : 
	_playerIndex(playerIndex)
{
}

Figure::~Figure()
{
	delete _figureImageBox;
}

void Figure::SetImageBox(ImageBox* imageBox)
{
	_figureImageBox = imageBox;
}

ImageBox* Figure::GetImageBox()
{
	return _figureImageBox;
}

void Figure::MoveTo(int x, int y)
{
	_figureImageBox->SetPosition(x, y); // todo add animator
}

void Figure::Resize(int w, int h)
{
	_figureImageBox->SetSize(w, h); // todo add animator
}

Player Figure::GetOwner()
{
	return _owner;
}

void Figure::SetOwner(Player owner)
{
	_owner = owner;
}