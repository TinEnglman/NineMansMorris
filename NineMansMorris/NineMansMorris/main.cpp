#include <iostream>

#include "Window.h"
#include "Renderer.h"


int main(int argc, char **argv)
{
	Renderer *renderer = new Renderer();
	Window *window = new Window("Nine Mans Morris", 1024, 768);
	window->Init();
	renderer->Init(window->GetWindow());
	window->SetRenderer(renderer);
	
	while (!window->IsClosed())
	{
		window->PollEvents();
		window->Clear();
	}

	return 0;
}