#pragma once
#include "ImageBox.h"
#include "Constants.h"


class Figure
{
public:
	Figure(int playerIndex);
	~Figure();
	void SetImageBox(ImageBox* imageBox);
	ImageBox* GetImageBox();
	void MoveTo(int x, int y);
	void Resize(int w, int h);
	Player GetOwner();
	void SetOwner(Player owner);

private:
	ImageBox* _figureImageBox = nullptr;
	int _playerIndex = 0;
	Player _owner = Player::NONE;

};