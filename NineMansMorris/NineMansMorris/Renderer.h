#pragma once

#include <SDL.h>

class Renderer
{
public:
	Renderer(SDL_Window *window);
	~Renderer();

	bool Init();
	SDL_Renderer* GetRenderer();

private:
	SDL_Renderer *_renderer = nullptr;
	SDL_Window* _window = nullptr;

};