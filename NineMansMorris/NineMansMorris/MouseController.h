#pragma once

#include <functional>
#include <SDL.h>

class MouseController
{
public:
	MouseController();
	void UpdateMotion(SDL_MouseMotionEvent* motionEvent);
	void ButtonUp(SDL_MouseButtonEvent* buttonEvent);
	void ButtonDown(SDL_MouseButtonEvent* buttonEvent);

	inline bool IsPointerPressed() { return _mouseDown; }
	int GetMousePositionX();
	int GetMousePositionY();
	void SetPressedCallback(std::function< void() > pressedCallback);
	void SetReleasedCallback(std::function< void() > releasedCallback);

private:
	std::function< void() > _onPointerPressedCallback;
	std::function< void() > _onPointerReleasedCallback;
	bool _mouseDown = false;
	int _mouseX = 0;
	int _mouseY = 0;
};
