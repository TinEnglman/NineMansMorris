#pragma once

#include <SDL_image.h>

#include "Window.h"
#include "ViewBox.h"

class ImageBox : ViewBox
{
public:
	ImageBox(Window *window, Renderer* renderer, int x, int y, int w, int h, const std::string &path);
	~ImageBox();

	virtual void Draw();
	void SetPosition(int x, int y);

private:
	SDL_Texture* _texture = nullptr;
};
