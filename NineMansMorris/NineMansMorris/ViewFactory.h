#pragma once

#include <string>

#include "ImageBox.h"
#include "TextBox.h"
#include "SceneManager.h"

class ViewFactory
{
public:
	ViewFactory(Window* window, Renderer* renderer);
	TextBox* CreateTextBox(int x, int y, int w, int h, const std::string text);
	ImageBox* CreateImageBox(int x, int y, int w, int h, const std::string path);

private:
	Window* _window = nullptr;
	Renderer* _renderer = nullptr;
};