#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "ImageBox.h"
#include "SceneManager.h"
#include "ViewFactory.h"


int main(int argc, char **argv)
{
	Renderer* renderer = new Renderer();
	Window* window = new Window("Nine Mans Morris", 768, 1024);
	window->Init();
	renderer->Init(window->GetWindow());
	window->SetRenderer(renderer);

	SceneManager* sceneManager = new SceneManager();
	ViewFactory* viewFactory = new ViewFactory(window, renderer);

	auto background = viewFactory->CreateImageBox(0, 256, 768, 768, "background.png");
	sceneManager->AddViewBox((ViewBox*)background);
	
	auto whitePiece = viewFactory->CreateImageBox(128, 256 + 128, 48, 48, "white_figure.png");
	sceneManager->AddViewBox((ViewBox*)whitePiece);

	auto blackPiece = viewFactory->CreateImageBox(64, 256 + 64, 48, 48, "black_figure.png");
	sceneManager->AddViewBox((ViewBox*)blackPiece);
	
	while (!window->IsClosed())
	{
		window->PollEvents();
		window->Clear();
		sceneManager->Draw();
		window->Present();
	}

	return 0;
}