#include <iostream>

#include "Renderer.h"


Renderer::Renderer()
{
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

bool Renderer::Init(SDL_Window *window)
{
	_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer.\n";
		return false;
	}
	
	return true;
}