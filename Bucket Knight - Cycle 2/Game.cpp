#include "TextureManager.h"
#include "TileMap.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

TileMap* map;
Manager manager;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

std::vector<ColliderComponent*> Game::colliders;

Game::Game()
{
	this->isRunning = true;
	this->window = nullptr;
}

Game::~Game()
{
	this->isRunning = false;
}

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

		map = new TileMap();
			
		TileMap::LoadTiles("Assets/test.txt", 10, 3);

		player.addComponent<TransformComponent>(0, 0, 24, 24, 2);
		player.addComponent<SpriteComponent>("Assets/Bucket Knight Concept.png");
		player.addComponent<KeyboardController>();
		player.addComponent<ColliderComponent>("player");
		player.addGroup(groupPlayers);

		wall.addComponent<TransformComponent>(300, 300, 300, 20);
		wall.addComponent<SpriteComponent>("Assets/FloorTexture.png");
		wall.addComponent<ColliderComponent>("wall");
		wall.addGroup(groupMap);
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
	manager.refresh();
	manager.update();

	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& e : enemies)
	{
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 24, 24, id);
	tile.addGroup(groupMap);
}
