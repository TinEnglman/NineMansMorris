#include "MouseController.h"


MouseController::MouseController()
{
}

void MouseController::ButtonDown(SDL_MouseButtonEvent* buttonEvent)
{
	if (buttonEvent->button == SDL_BUTTON_LEFT)
	{
		_onPointerPressedCallback();
		_mouseDown = true;

	}
}

void MouseController::ButtonUp(SDL_MouseButtonEvent* buttonEvent)
{
	if (buttonEvent->button == SDL_BUTTON_LEFT)
	{
		_onPointerReleasedCallback();
		_mouseDown = false;
	}
}

void MouseController::UpdateMotion(SDL_MouseMotionEvent* motionEvent)
{
	_mouseX = motionEvent->x;
	_mouseY = motionEvent->y;
}

int MouseController::GetMousePositionX()
{
	return _mouseX;
}

int MouseController::GetMousePositionY()
{
	return _mouseY;
}

void MouseController::SetPressedCallback(std::function< void() > pressedCallback)
{
	_onPointerPressedCallback = pressedCallback;
}
void MouseController::SetReleasedCallback(std::function< void() > releasedCallback)
{
	_onPointerReleasedCallback = releasedCallback;
}