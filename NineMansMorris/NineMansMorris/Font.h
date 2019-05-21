#pragma once

#include <string>
#include <SDL_ttf.h>

class Font
{
public:
	Font(const std::string path);

	TTF_Font* GetFont();

private:
	TTF_Font* _font = nullptr;
};

