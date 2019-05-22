#include "MouseController.h"

MouseController::MouseController(int intialMouseX, int initialMouseY) :
	_mouseX(intialMouseX), _mouseY(initialMouseY)
{
}

void MouseController::ButtonDown(SDL_MouseButtonEvent* buttonEvent)
{
	if (buttonEvent->button == SDL_BUTTON_LEFT)
	{
		_mouseDown = true;
	}
}

void MouseController::ButtonUp(SDL_MouseButtonEvent* buttonEvent)
{
	if (buttonEvent->button == SDL_BUTTON_LEFT)
	{
		_mouseDown = false;
	}
}

void MouseController::UpdateMotion(SDL_MouseMotionEvent* motionEvent)
{
	_mouseX = motionEvent->x;
	_mouseY = motionEvent->y;
}

bool MouseController::IsPointerPressed()
{
	return _mouseDown;
}

int MouseController::GetMousePositionX()
{
	return _mouseX;
}

int MouseController::GetMousePositionY()
{
	return _mouseY;
}