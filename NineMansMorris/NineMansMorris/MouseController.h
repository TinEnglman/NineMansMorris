#pragma once

#include <SDL.h>

class MouseController
{
public:
	MouseController(int initialMouseX, int initialMouseY);
	void UpdateMotion(SDL_MouseMotionEvent* motionEvent);
	void ButtonUp(SDL_MouseButtonEvent* buttonEvent);
	void ButtonDown(SDL_MouseButtonEvent* buttonEvent);

	bool IsPointerPressed();
	int GetMousePositionX();
	int GetMousePositionY();

private:
	bool _mouseDown = false;
	int _mouseX;
	int _mouseY;
};
