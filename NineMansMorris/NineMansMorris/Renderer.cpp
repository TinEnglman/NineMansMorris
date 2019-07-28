#include <iostream>

#include "Renderer.h"


Renderer::Renderer(SDL_Window *window)
{
	_window = window;
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

SDL_Renderer* Renderer::GetRenderer()
{
	return _renderer;
}

bool Renderer::Init()
{
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer.\n";
		return false;
	}
	
	return true;
}