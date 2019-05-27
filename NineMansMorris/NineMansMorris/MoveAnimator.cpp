#include "MoveAnimator.h"

MoveAnimation::MoveAnimation(ImageBox* animated, int destination_x, int destination_y, float duration) :
	_animated(animated), _destinationX(destination_x), _destinationY(destination_y), _duration(duration)

{
	_time = 0;
	_sourceX = animated->GetPostionX();
	_sourceY = animated->GetPostionY();
}

void MoveAnimation::Update(float dt)
{
	_time += dt;

	if (_time < _duration)
	{
		float timer = _time / _duration;

		float currentX = _sourceX + (_destinationX - _sourceX) * timer;
		float currentY = _sourceY + (_destinationY - _sourceY)* timer;

		_animated->SetPosition((int)currentX, (int)currentY);
	}
	else
	{
		_time = _duration;
		_animated->SetPosition(_destinationX, _destinationY);
	}
}

bool MoveAnimation::IsDone()
{
	return _time >= _duration;
}