#include <iostream>

#include "Window.h"


Window::Window(const std::string &title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	_closed = false;
}

Window::~Window()
{
	SDL_DestroyWindow(_window);
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
	return true;
}

void Window::PollEvents()
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

SDL_Window* Window::GetWindow()
{
	return _window;
}

void Window::SetRenderer(Renderer* renderer)
{
	_renderer = renderer;
}


void Window::Clear() const // ripe for refactor
{
	SDL_SetRenderDrawColor(_renderer->GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(_renderer->GetRenderer());
	SDL_RenderPresent(_renderer->GetRenderer());
}