#include "Window.h"

#include <iostream>

Window::Window(const std::string &title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	_closed = !Init();
}

Window::~Window()
{
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

bool Window::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed to initalize SDL.\n";
		return false;
	}

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);

	if (_window == nullptr)
	{
		std::cerr << "Failed to create window.\n";
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer.\n";
		return false;
	}

	return true;
}

void Window::pollEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_closed = true;
			break;
		default:
			break;
		}
	}
}

void Window::clear() const
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
	SDL_RenderClear(_renderer);

	SDL_Rect rect;
	rect.w = 120;
	rect.h = 120;
	rect.x = _width / 2 - rect.w / 2;
	rect.y = _height / 2 - rect.h / 2;

	SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 200);
	SDL_RenderFillRect(_renderer, &rect);

	SDL_RenderPresent(_renderer);
}