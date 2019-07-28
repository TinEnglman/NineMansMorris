#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "ImageBox.h"
#include "SceneManager.h"
#include "ViewFactory.h"
#include "EventController.h"
#include "GameController.h"
#include "BoardFactory.h"
#include "Animator.h"


int main(int argc, char **argv)
{
	
	Window* window = new Window("Nine Mans Morris", SCREEN_W, SCREEN_H);
	window->Init();

	Renderer* renderer = new Renderer(window->GetWindow());
	renderer->Init();
	
	window->SetRenderer(renderer);

	Font* font = new Font("arial.ttf");
	ViewFactory* viewFactory = new ViewFactory(window, renderer, font);
	Animator* animator = new Animator();
	SceneManager* sceneManager = new SceneManager(viewFactory, animator);

	sceneManager->SetupBackground();
	sceneManager->SetupGUI();
	sceneManager->SetupInitialSlots();
	sceneManager->SetupBoardSlots();

	BoardFactory* boardFactory = new BoardFactory();
	Board *board = boardFactory->CreateBoard();

	Game* game = new Game(board, sceneManager);
	game->Setup();
	MouseController* mouseController = new MouseController();
	GameController* gameController = new GameController(game, mouseController, sceneManager);
	EventController* eventController = new EventController(window, mouseController, gameController);
	gameController->Setup();
	

	while (!window->IsClosed())
	{
		eventController->PollEvents();
		animator->Update();
		window->Clear();
		sceneManager->Draw();
		window->Present();
	}

	return 0;
}