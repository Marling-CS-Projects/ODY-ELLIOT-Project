#include "TextureManager.h"
#include "Components.h"
#include "Vector2D.h"

Manager manager;
auto& player(manager.addEntity());
SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	int flags = 0;
	
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	else
	{
		flags = SDL_WINDOW_RESIZABLE;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window)
		{
			std::cout << "Window Created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer Created" << std::endl;
		}

		isRunning = true;

		player.addComponent<TransformComponent>();
		player.addComponent<SpriteComponent>("Assets/Bucket Knight Concept.png");
		player.addComponent<KeyboardController>();
	}

	else
	{
		isRunning = false;
	}

}

void Game::handleEvents()
{
	
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{
	manager.update();
	player.update();
	std::cout << player.getComponent<TransformComponent>().position.x << "," <<
		player.getComponent<TransformComponent>().position.y << std::endl;

}

void Game::render()
{
	SDL_RenderClear(renderer);
	player.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}
