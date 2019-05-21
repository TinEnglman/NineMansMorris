#pragma once

#include <string>

#include "Window.h"

class ViewBox
{
public:
	virtual void Draw() = 0;

protected:
	int _x, _y;
	int _w, _h;
	std::string path;
	Window* _window;
	Renderer* _renderer;

};
