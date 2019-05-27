#include "EventController.h"

EventController::EventController(Window* window, MouseController* mouseController, GameController* gameController ) :
	_window(window), _mouseController(mouseController), _gameController(gameController)
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
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				_gameController->Reset();
			}
			break;
		case SDL_MOUSEMOTION:
			_mouseController->UpdateMotion(&event.motion);
		default:
			break;
		}
	}
}