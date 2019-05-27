#pragma once

#include <vector>

#include "Animation.h"

class Animator
{
public:
	Animator();
	void AddAnimation(Animation* animation);

	void Update();

private:

	std::vector<Animation*> _animations; 
	std::vector<Animation*> _killList;
	Uint32 _previousTicks = 0;
};