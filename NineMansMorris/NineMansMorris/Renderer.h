#pragma once

#include <SDL.h>

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Init(SDL_Window *window);
	SDL_Renderer* GetRenderer();

private:
	SDL_Renderer *_renderer = nullptr;

};