#include "ViewFactory.h"


ViewFactory::ViewFactory(Window* window, Renderer* renderer) :
	_window(window), _renderer(renderer)
{
}

ImageBox* ViewFactory::CreateImageBox(int x, int y, int w, int h, const std::string path)
{
	ImageBox* imageBox = new ImageBox(_window, _renderer, x, y, w, h, "res/" + path);
	return imageBox;
}


TextBox* ViewFactory::CreateTextBox(int x, int y, int w, int h, const std::string path)
{
	//ImageBox* background = new TextBox(_window, _renderer, x, y, w, h, "res/" + path); // todo
	//_sceneManager->AddViewBox((ViewBox*)background);
	return new TextBox(); // todo
}