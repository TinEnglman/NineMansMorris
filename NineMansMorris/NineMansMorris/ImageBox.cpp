#include <iostream>
#include "ImageBox.h"

ImageBox::ImageBox(Window *window, Renderer* renderer, int x, int y, int w, int h, const std::string &path)
{
	_window = window;
	_renderer = renderer;
	_x = x;
	_y = y;
	_w = w;
	_h = h;
	
	auto surface = IMG_Load(path.c_str());
	if (!surface)
	{
		std::cerr << "Failed to create surface. \n";
	}

	_texture = SDL_CreateTextureFromSurface(_renderer->GetRenderer(), surface);

	if (!_texture)
	{
		std::cerr << "Failed to create texture. \n";
	}
	SDL_FreeSurface(surface);
}


ImageBox::~ImageBox()
{
	SDL_DestroyTexture(_texture);
}

void ImageBox::Draw()
{
	SDL_Rect rect = { _x, _y, _w, _h };
	if (!_texture)
	{
		std::cerr << "Texture is nil. \n";
	}
	
	if (SDL_RenderCopy(_renderer->GetRenderer(), _texture, NULL, &rect) == -1)
	{
		std::cerr << "Failed to display ImageBox. \n";
	}
}

void ImageBox::SetPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void ImageBox::SetSize(int w, int h)
{
	_w = w;
	_h = h;
}

int ImageBox::GetPostionX()
{
	return _x;
}
int ImageBox::GetPostionY()
{
	return _y;
}
int ImageBox::GetSizeW()
{
	return _w;
}
int ImageBox::GetSizeH()
{
	return _h;
}