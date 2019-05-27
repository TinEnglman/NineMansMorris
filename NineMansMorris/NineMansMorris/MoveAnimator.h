#pragma once

#include <cmath>

#include "Animation.h"
#include "ImageBox.h"


class MoveAnimation : Animation
{
public:
	MoveAnimation(ImageBox* animated, int destination_x, int destination_y, float duration);

	virtual void Update(float dt);
	virtual bool IsDone();

private:
	ImageBox* _animated = nullptr;
	int _destinationX = 0;
	int _destinationY = 0;
	int _sourceX = 0;
	int _sourceY = 0;
	float _duration = 0;
	float _time = 0;
};