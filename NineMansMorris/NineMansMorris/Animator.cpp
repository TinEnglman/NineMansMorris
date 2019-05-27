#include <SDL.h>

#include "Animator.h"
#include "Global.h"


Animator::Animator()
{
}

void Animator::AddAnimation(Animation* animation)
{
	_animations.push_back(animation);
}

void Animator::Update()
{
	Uint32 ticks = SDL_GetTicks();
	float dt = (ticks - _previousTicks) / (float)FPS;

	for (Animation* animation : _animations)
	{
		animation->Update(dt);

		if (animation->IsDone())
		{
			_killList.push_back(animation);
		}
	}

	for (Animation* animation : _killList)
	{
		int index = -1;
		for (unsigned int i = 0; i < _animations.size(); i++)
		{
			if (_animations[i] == animation)
			{
				index = i;
				break;
			}
		}

		if (index != -1)
		{
			delete animation;
			_animations.erase(_animations.begin() + index);
		}
	}
	
	_killList.clear();
	_previousTicks = ticks;
}
