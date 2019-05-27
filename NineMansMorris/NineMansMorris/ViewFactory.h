#pragma once

#include <string>

#include "ImageBox.h"
#include "TextBox.h"
#include "Font.h"


class ViewFactory
{
public:
	ViewFactory(Window* window, Renderer* renderer, Font* font);
	TextBox* CreateTextBox(int x, int y, int w, int h, const std::string text);
	ImageBox* CreateImageBox(int x, int y, int w, int h, const std::string path);

private:
	Window* _window = nullptr;
	Renderer* _renderer = nullptr;
	Font* _font = nullptr;
};