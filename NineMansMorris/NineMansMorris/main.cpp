#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "ImageBox.h"
#include "SceneManager.h"
#include "ViewFactory.h"
#include "EventController.h"
#include "GameController.h"
#include "BoardFactory.h"


int main(int argc, char **argv)
{
	const int SCREEN_W = 768;
	const int SCREEN_H = 1024;

	Renderer* renderer = new Renderer();
	Window* window = new Window("Nine Mans Morris", SCREEN_W, SCREEN_H);
	window->Init();
	renderer->Init(window->GetWindow());
	window->SetRenderer(renderer);

	MouseController* mouseController = new MouseController();
	EventController* eventController = new EventController(window, mouseController);
	
	Font* font = new Font("arial.ttf");
	ViewFactory* viewFactory = new ViewFactory(window, renderer, font);
	SceneManager* sceneManager = new SceneManager(viewFactory);

	sceneManager->SetupBackground();
	sceneManager->SetupGUI();
	sceneManager->SetupInitialSlots();
	sceneManager->SetupBoardSlots();
	
	BoardFactory* boardFactory = new BoardFactory();
	Board *board = boardFactory->CreateBoard();

	GameController* gameController = new GameController(board, mouseController, sceneManager);
	gameController->Setup();

	while (!window->IsClosed())
	{
		eventController->PollEvents();
		gameController->Update();
		window->Clear();
		sceneManager->Draw();
		window->Present();
	}

	return 0;
}