#pragma once

#include <SDL.h>

class MouseController
{
public:
	MouseController();
	void UpdateMotion(SDL_MouseMotionEvent* motionEvent);
	void ButtonUp(SDL_MouseButtonEvent* buttonEvent);
	void ButtonDown(SDL_MouseButtonEvent* buttonEvent);

	bool IsPointerPressed();
	int GetMousePositionX();
	int GetMousePositionY();

private:
	bool _mouseDown = false;
	int _mouseX = 0;
	int _mouseY = 0;
};
