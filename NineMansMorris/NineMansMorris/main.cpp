#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "ImageBox.h"
#include "SceneManager.h"
#include "ViewFactory.h"


int main(int argc, char **argv)
{
	const int screenW = 768;
	const int screenH = 1024;

	Renderer* renderer = new Renderer();
	Window* window = new Window("Nine Mans Morris", screenW, screenH);
	window->Init();
	
	renderer->Init(window->GetWindow());
	window->SetRenderer(renderer);


	SceneManager* sceneManager = new SceneManager();
	Font* font = new Font("arial.ttf");
	ViewFactory* viewFactory = new ViewFactory(window, renderer, font);

	auto background = viewFactory->CreateImageBox(0, 256, 768, 768, "background.png"); // move to scene manage
	sceneManager->AddViewBox((ViewBox*)background);
	
	auto topPannel = viewFactory->CreateImageBox(0, 0, 768, 256, "top_pannel.png");
	sceneManager->AddViewBox((ViewBox*)topPannel);
	
	auto whitePiece = viewFactory->CreateImageBox(128, 256 + 128, 48, 48, "white_figure.png");
	sceneManager->AddViewBox((ViewBox*)whitePiece);

	auto blackPiece = viewFactory->CreateImageBox(64, 256 + 64, 48, 48, "black_figure.png");
	sceneManager->AddViewBox((ViewBox*)blackPiece);

	auto playerLabel1 = viewFactory->CreateTextBox(10, 10, 400, 100, "PLAYER 1");
	playerLabel1->SetColor(255, 255, 0);
	sceneManager->AddViewBox((ViewBox*)playerLabel1);

	auto playerLabel2 = viewFactory->CreateTextBox(screenH - 400 - 60, 10, 400, 100, "PLAYER 2");
	playerLabel2->SetColor(255, 255, 0);
	sceneManager->AddViewBox((ViewBox*)playerLabel2);
	
	while (!window->IsClosed())
	{
		window->PollEvents();
		window->Clear();
		sceneManager->Draw();
		window->Present();
	}

	return 0;
}