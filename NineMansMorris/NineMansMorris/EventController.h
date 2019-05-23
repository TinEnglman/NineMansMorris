#pragma once
#include <SDL.h>

#include "Window.h"
#include "MouseController.h"

class EventController
{
public:
	EventController(Window* window, MouseController* mouseController);
	void PollEvents();
private:
	Window* _window = nullptr;
	MouseController* _mouseController= nullptr;
};