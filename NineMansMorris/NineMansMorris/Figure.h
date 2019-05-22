#pragma once
#include "ImageBox.h"


class Figure
{
public:
	Figure(int playerIndex);
	void SetImageBox(ImageBox* imageBox);
	void MoveTo(int x, int y);
	void Resize(int w, int h);

private:
	ImageBox* _figureImageBox = nullptr;
	int _playerIndex = 0;

};