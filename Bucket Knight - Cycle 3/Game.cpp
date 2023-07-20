#include "TextureManager.h"
#include "TileMap.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Dungeon.h"
#include "Objects.h"

Manager manager;
Dungeon* dGen = nullptr;
TileMap* map = nullptr;

auto forwardTrigger = new Trigger();
auto backTrigger = new Trigger();

std::vector<string> Dungeon::GetRooms()
{
	vector<string> temp{
		"RoomSTART",
		"RoomEND",
		"Room1",
		"Room2",
		"Room3",
		"Room4",
		"Room5"
	};

	return temp;
}

enum groupLabels : std::size_t
{
	groupBackground,
	groupForeground,
	groupPlayers,
	groupEnemies,
	groupColliders
};

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
vector<Entity*> oldtiles{};

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

		SDL_RenderSetLogicalSize(renderer, width, height);

		isRunning = true;

		/*
		
		Implementation
		
		*/

		auto player = new Player();
		player->CreatePlayer(400, 300);
		player->gameObject->addGroup(groupPlayers);

		auto wall1 = new Wall();
		wall1->CreateWall(204, 120, 432, 24, "Assets/FloorTexture2.png");
		wall1->gameObject->addGroup(groupForeground);

		auto wall2 = new Wall();
		wall2->CreateWall(204, 528, 432, 24, "Assets/FloorTexture2.png");
		wall2->gameObject->addGroup(groupForeground);

		forwardTrigger->CreateTrigger(612, 120, 24, 432, "Assets/FloorTexture.png", "forwardTrigger");
		forwardTrigger->gameObject->addGroup(groupForeground);

		backTrigger->CreateTrigger(204, 120, 24, 432, "Assets/FloorTexture.png", "backTrigger");
		backTrigger->gameObject->addGroup(groupForeground);

		dGen = new Dungeon(100);
		dGen->GenerateLayout();
		dGen->DrawCurrentRoom();
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

auto& background(manager.getGroup(groupBackground));
auto& foreground(manager.getGroup(groupForeground));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

void Game::update()
{
	manager.refresh();
	manager.update();
	
	for (auto cc : colliders)
	{
		for (auto& p : players)
		{
			if (p->hasComponent<ColliderComponent>()) {
				if (cc->tag == "backTrigger" && Collision::AABB(p->getComponent<ColliderComponent>(), *cc))
				{
					dGen->currentRoom -= 1;
					p->getComponent<TransformComponent>().position = Vector2D(300, 240);
					dGen->DrawCurrentRoom();
					std::cout << dGen->currentRoom+1 << std::endl;
				}
				else if (cc->tag == "forwardTrigger" && Collision::AABB(p->getComponent<ColliderComponent>(), *cc))
				{
					dGen->currentRoom += 1;
					p->getComponent<TransformComponent>().position = Vector2D(300, 240);
					dGen->DrawCurrentRoom();
					std::cout << dGen->currentRoom+1 << std::endl;
				}

				if (cc->tag == "wall" && Collision::AABB(p->getComponent<ColliderComponent>(), *cc))
				{
					p->getComponent<TransformComponent>().position = p->getComponent<TransformComponent>().previousPos;
				}
			}
		}
		for (auto& e : enemies)
		{
			if (e->hasComponent<ColliderComponent>()) {
				Collision::AABB(e->getComponent<ColliderComponent>(), *cc);
			}
		}
	}
	
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& b : background)
	{
		b->draw();
	}
	for (auto& f : foreground)
	{
		f->draw();
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
	oldtiles.push_back(&tile);
	tile.addComponent<TileComponent>(x + 228, y + 144, 24, 24, id);
	tile.addGroup(groupBackground);
}

void Level::BuildLevel()
{

	for (Entity* i : oldtiles)
	{
		if (i->isActive())
		{
			i->destroy();
		}
		
	}
	oldtiles.clear();

	map->LoadTiles(lvlName + ".txt", x, y);

	if (this->tag == "end")
	{

	}
}

void Object::CreateObject()
{
	auto& g(manager.addEntity());
	gameObject = &g;
}

void Object::DeleteObject()
{
	gameObject->destroy();
}