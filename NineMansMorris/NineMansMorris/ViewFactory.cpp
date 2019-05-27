#include "ViewFactory.h"


ViewFactory::ViewFactory(Window* window, Renderer* renderer, Font* font) :
	_window(window), _renderer(renderer), _font(font)
{
}

ImageBox* ViewFactory::CreateImageBox(int x, int y, int w, int h, const std::string path)
{
	ImageBox* imageBox = new ImageBox(_window, _renderer, x, y, w, h, "res/textures/" + path);
	return imageBox;
}


TextBox* ViewFactory::CreateTextBox(int x, int y, int w, int h, const std::string text)
{
	TextBox* textBox = new TextBox(_window, _renderer, x, y, w, h, text, _font);
	return textBox;
}