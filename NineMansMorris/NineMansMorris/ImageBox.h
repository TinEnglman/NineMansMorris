#pragma once

#include <SDL_image.h>

#include "Window.h"

class ImageBox
{
public:
	ImageBox(Window *window, Renderer* renderer, int x, int y, int w, int h, const std::string &path);
	~ImageBox();

	void Draw();

private:
	int _x, _y;
	int _w, _h;
	std::string path;
	Window* _window;
	Renderer* _renderer;
	SDL_Texture* _texture = nullptr;

};
