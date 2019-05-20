#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "Renderer.h"


class Window
{
public:
	Window(const std::string &title, int width, int height);
	~Window();

	
	inline bool IsClosed() const { return _closed; };
	bool Init(); 
	void PollEvents();
	void Clear() const;
	void Present() const;
	SDL_Window* GetWindow();
	void SetRenderer(Renderer* renderer);

private:
	std::string _title;
	int _width = 0;
	int _height = 0;

	bool _closed = false;
	SDL_Window *_window = nullptr;
	Renderer* _renderer = nullptr;
};
