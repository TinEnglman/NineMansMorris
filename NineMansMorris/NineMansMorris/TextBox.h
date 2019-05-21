#pragma once

#include <string>

#include "ViewBox.h"
#include "Font.h"


class TextBox : ViewBox
{
public:
	TextBox(Window *window, Renderer* renderer, int x, int y, int w, int h, const std::string &text, Font* font);
	virtual void Draw();
	void SetColor(int red, int green, int blue);

private:

	void Refresh();

	std::string _text;
	Font* _font;
	SDL_Texture* _texture = nullptr;
	SDL_Color _textColor = {255, 255, 255, 255};

};