#include "TextBox.h"
#include <iostream>


TextBox::TextBox(Window *window, Renderer* renderer, int x, int y, int w, int h, const std::string &text, Font* font)
{
	_window = window;
	_renderer = renderer;
	_font = font;
	_text = text;
	_x = x;
	_y = y;
	_w = w;
	_h = h;
	
	Refresh();
}

void TextBox::Draw()
{
	SDL_Rect rect = {_x, _y, _w, _h};
	SDL_RenderCopy(_renderer->GetRenderer(), _texture, NULL, &rect);
}

void TextBox::SetColor(int r, int g, int b)
{
	SDL_Color color = { (Uint8)r, (Uint8)g, (Uint8)b, _textColor.a};
	_textColor = color;
	Refresh();
}

void TextBox::Refresh()
{
	SDL_Surface* surface = TTF_RenderText_Blended(_font->GetFont(), _text.c_str(), _textColor);
	_texture = SDL_CreateTextureFromSurface(_renderer->GetRenderer(), surface);

	if (!_texture)
	{
		std::cerr << "Failed to create texture. \n";
	}

	SDL_QueryTexture(_texture, nullptr, nullptr, &_w, &_h);
	SDL_FreeSurface(surface);
}
void TextBox::SetText(std::string text)
{
	_text = text;
	Refresh();
}
std::string TextBox::GetText()
{
	return _text;
}
