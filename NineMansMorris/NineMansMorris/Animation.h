#pragma once

class Animation
{
public:
	virtual void Update(float dt) = 0;
	virtual bool IsDone() = 0;
};