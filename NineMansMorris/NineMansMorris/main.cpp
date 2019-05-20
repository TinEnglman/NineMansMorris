#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "ImageBox.h"


int main(int argc, char **argv)
{
	Renderer* renderer = new Renderer();
	Window* window = new Window("Nine Mans Morris", 768, 1024);
	window->Init();
	renderer->Init(window->GetWindow());
	window->SetRenderer(renderer);

	ImageBox* background = new ImageBox(window, renderer, 0, 256, 768, 768, "res/background.png");
	ImageBox* whiteFigure = new ImageBox(window, renderer, 128, 256 + 128, 48, 48, "res/white_figure.png");
	ImageBox* blackFigure = new ImageBox(window, renderer, 64, 256 + 64, 48, 48, "res/black_figure.png");
	
	while (!window->IsClosed())
	{
		window->PollEvents();
		window->Clear();
		background->Draw();
		whiteFigure->Draw();
		blackFigure->Draw();
		window->Present();
	}

	return 0;
}