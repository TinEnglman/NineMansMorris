#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Window.h"


Window::Window(const std::string &title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	_closed = false;
}

Window::~Window()
{
	SDL_DestroyWindow(_window);
	IMG_Quit();
	TTF_Quit();
}

bool Window::Init() // to much responsibility, refactor
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed to initalize SDL.\n";
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cerr << "Failed to initalize SDL image. \n";
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


void Window::Clear() const
{
	SDL_SetRenderDrawColor(_renderer->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(_renderer->GetRenderer());
}

void Window::Present() const
{
	SDL_RenderPresent(_renderer->GetRenderer());
}