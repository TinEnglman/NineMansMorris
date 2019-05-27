#pragma once
#include <SDL.h>

#include "Window.h"
#include "MouseController.h"
#include "GameController.h"

class EventController
{
public:
	EventController(Window* window, MouseController* mouseController, GameController* gameController);
	void PollEvents();
private:
	Window* _window = nullptr;
	MouseController* _mouseController = nullptr;
	GameController* _gameController = nullptr;

};