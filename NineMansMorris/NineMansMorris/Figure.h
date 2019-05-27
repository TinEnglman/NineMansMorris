#pragma once
#include "ImageBox.h"
#include "Global.h"
#include "Animator.h"
#include "MoveAnimator.h"

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
	void SetAnimator(Animator* animator);

private:
	ImageBox* _figureImageBox = nullptr;
	int _playerIndex = 0;
	Player _owner = Player::NONE;
	Animator* _animator = nullptr;

};