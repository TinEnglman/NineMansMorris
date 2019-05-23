#include "EventController.h"

EventController::EventController(Window* window, MouseController* mouseController) :
	_window(window), _mouseController(mouseController)
{
}

void EventController::PollEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_window->Close();
			break;
		case SDL_MOUSEBUTTONDOWN:
			_mouseController->ButtonDown(&event.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_mouseController->ButtonUp(&event.button);
			break;
		case SDL_MOUSEMOTION:
			_mouseController->UpdateMotion(&event.motion);
		default:
			break;
		}
	}
}