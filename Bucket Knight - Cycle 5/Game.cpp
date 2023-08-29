#include "TextureManager.h"
#include "TileMap.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Dungeon.h"
#include "Objects.h"

Manager manager;
Dungeon* dGen = nullptr;
TileMap* map = nullptr;

auto player = new Player();
Game* gameRef;

int MouseX, MouseY = 0;
float w, h = 0;
float scaleX, scaleY = 1;

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
	groupBullets,
	groupColliders
};

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
vector<Entity*> oldtiles{};

std::vector<ColliderComponent*> Game::colliders;

Game::Game(Game* game)
{
	this->isRunning = true;
	this->window = nullptr;
	this->game = game;
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

		gameRef = this->GetGameReference();
		
		player->CreatePlayer(400, 300, 3);
		player->entity->addGroup(groupPlayers);

		auto heart1 = new PlayerHeart(12, 12, &player->entity->getComponent<PlayerComponent>(), 1);
		heart1->entity->addGroup(groupForeground);

		auto heart2 = new PlayerHeart(60, 12, &player->entity->getComponent<PlayerComponent>(), 2);
		heart2->entity->addGroup(groupForeground);

		auto heart3 = new PlayerHeart(108, 12, &player->entity->getComponent<PlayerComponent>(), 3);
		heart3->entity->addGroup(groupForeground);

		auto wall1 = new Wall(204, 120, 432, 24, "Assets/FloorTexture2.png");
		wall1->entity->addGroup(groupForeground);

		auto wall2 = new Wall(204, 528, 432, 24, "Assets/FloorTexture2.png");
		wall2->entity->addGroup(groupForeground);

		auto wall3 = new Wall(612, 120, 24, 432, "Assets/FloorTexture2.png");
		wall3->entity->addGroup(groupForeground);

		auto wall4 = new Wall(204, 120, 24, 432, "Assets/FloorTexture2.png");
		wall4->entity->addGroup(groupForeground);

		dGen = new Dungeon(10);
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

	if (Game::event.type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&MouseX, &MouseY);
		windowMousePositionToLogicalMousePosition(renderer, window, MouseX, MouseY);
	}

	if (Game::event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (SDL_BUTTON_LEFT == Game::event.button.button)
		{
			Vector2D dir{ (float)MouseX - player->GetTransform().position.x, (float)MouseY- player->GetTransform().position.y };
			dir = dir.normalize(dir);
			auto bullet = new Bullet();
			bullet->CreateBullet(player->GetTransform().position.x, player->GetTransform().position.y, 12, 12, "Assets/FloorTexture2.png", "playerbullet", dir, 3, 1, 400);
			bullet->entity->addGroup(groupBullets);
		}
	}

	if (Game::event.type == SDL_MOUSEBUTTONUP)
	{
		if (SDL_BUTTON_LEFT == Game::event.button.button)
		{
			
		}
	}

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
auto& bullets = (manager.getGroup(groupBullets));

void Game::update()
{

	manager.refresh();
	manager.update();

	if (enemies.size() <= 0)
	{
		dGen->currentRoom += 1;
		for (auto& b : bullets) { b->destroy(); }
		for (auto& e : enemies)
		{
			if (!e->isActive())
			{
				e->delGroup(groupEnemies);
				e->destroy();
			}
		}
		player->entity->getComponent<TransformComponent>().position = Vector2D(300, 240);
		dGen->DrawCurrentRoom();
	}
	
	for (auto cc : colliders)
	{
		for (auto& p : players)
		{
			if (p->hasComponent<ColliderComponent>()) {
				if (cc->tag == "wall" && Collision::AABB(p->getComponent<ColliderComponent>(), *cc))
				{
					p->getComponent<TransformComponent>().position = p->getComponent<TransformComponent>().previousPos;
				}
			}

		}
		for (auto& e : enemies)
		{
			if (e->hasComponent<ColliderComponent>())
			{
				if (cc->tag == "playerbullet" && Collision::AABB(e->getComponent<ColliderComponent>(), *cc))
				{
					e->getComponent<MeleeEnemy>().hit();
					cc->entity->destroy();
				}

				if (cc->tag == "player" && Collision::AABB(e->getComponent<ColliderComponent>(), *cc))
				{
					cc->entity->getComponent<PlayerComponent>().hit(e);
				}
			}
		}
		for (auto& b : bullets)
		{
			if (cc->tag == "wall" && Collision::AABB(b->getComponent<ColliderComponent>(), *cc))
			{
				b->destroy();
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
	for (auto& b : bullets)
	{
		b->draw();
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

void Game::windowMousePositionToLogicalMousePosition(SDL_Renderer* renderer, SDL_Window* window, int realMouseX, int realMouseY) {
	int wWidth, wHeight;
	int rLogicalWidth, rLogicalHeight;
	int rRealWidth, rRealHeight;
	float rScaleX, rScaleY;
	int rMidpointY, wMidpointY;
	int rMidpointX, wMidpointX;
	int rY, rX;

	SDL_GetWindowSize(window, &wWidth, &wHeight);
	wMidpointY = wHeight / 2;
	wMidpointX = wWidth / 2;

	SDL_RenderGetLogicalSize(renderer, &rLogicalWidth, &rLogicalHeight);
	SDL_RenderGetScale(renderer, &rScaleX, &rScaleY);
	rRealWidth = (float)rLogicalWidth * (float)rScaleX;
	rRealHeight = (float)rLogicalHeight * (float)rScaleY;
	rMidpointY = rRealHeight / 2;
	rMidpointX = rRealWidth / 2;
	rY = wMidpointY - rMidpointY;
	rX = wMidpointX - rMidpointX;

	int adjustedMouseY = realMouseY - rY; // takes into account any border when keeping aspect ratio
	int adjustedMouseX = realMouseX - rX;
	MouseX = (float)adjustedMouseX / (float)rRealWidth * (float)rLogicalWidth;
	MouseY = (float)adjustedMouseY / (float)rRealHeight * (float)rLogicalHeight;

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
	SpawnEnemies();

	if (this->tag == "end")
	{

	}
}

void Level::SpawnEnemies()
{
	int x, y;
	auto p = player->GetTransform();

	for (int i = 0; i < this->numberOfEnemies; i++)
	{
		x = (rand() % (568 - 385)) + 385;
		y = (rand() % (478 - 140)) + 140;
		std::cout << "X: " + to_string(x) + ", Y: " + to_string(y) << std::endl;
		auto mE = new EMelee(x, y, 24, 24, "Assets/Goblin.png", "enemy", &p);
		mE->entity->addGroup(groupEnemies);
	}
}

void Object::CreateObject()
{
	auto& g(manager.addEntity());
	entity = &g;
}

void Object::DeleteObject()
{
	entity->destroy();
}

Game* Object::GetGame()
{
	return gameRef;
}

TransformComponent* Object::GetPlayerTransform()
{
	if (!player->entity->hasComponent<TransformComponent>())
	{
		auto o = new Object();
		o->AddTransform(0, 0, 24, 24, 1);
		return &o->entity->getComponent<TransformComponent>();
	}
	return &player->entity->getComponent<TransformComponent>();
}

const void Game::RemoveEnemyGroup(Entity* e)
{
	if (e->hasGroup(groupEnemies))
	{
		e->delGroup(groupEnemies);
	}
}