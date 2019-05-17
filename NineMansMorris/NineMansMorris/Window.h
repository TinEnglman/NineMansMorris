#pragma once

#include <string>
#include <SDL.h>

class Window
{
public:
	Window(const std::string &title, int width, int height);
	~Window();

	void pollEvents();
	void clear() const;
	
	inline bool isClosed() const { return _closed; };

private:
	bool Init();


private:
	std::string _title;
	int _width = 1024;
	int _height = 768;

	bool _closed = false;
	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;
};
