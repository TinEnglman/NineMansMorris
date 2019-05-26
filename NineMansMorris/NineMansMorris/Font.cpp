#include <iostream>
#include "Font.h"
#include "Global.h"


Font::Font(const std::string path)
{
	int fontSize = FONT_SIZE;
	std::string fullPath = "res/fonts/" + path;
	
	if (TTF_Init() == -1)
	{
		std::cerr << "Failed to initalize TTF. \n";
	}

	_font = TTF_OpenFont(fullPath.c_str(), fontSize);
	
	if (_font == nullptr)
	{
		std::cerr << "Failed to load font. \n";
	}
}

TTF_Font* Font::GetFont()
{
	return _font;
}