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
	void SetSize(int w, int h);
	int GetPostionX();
	int GetPostionY();
	int GetSizeW();
	int GetSizeH();

private:
	SDL_Texture* _texture = nullptr;
};
