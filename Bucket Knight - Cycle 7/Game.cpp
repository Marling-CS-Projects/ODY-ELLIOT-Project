#include "TextureManager.h"
#include "TileMap.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Dungeon.h"
#include "Objects.h"

// For Music
#include <SDL_mixer.h>

Mix_Music* music = nullptr;
Mix_Chunk* shoot = nullptr;
Mix_Chunk* enemyHit = nullptr;
Mix_Chunk* playerHit = nullptr;
Mix_Chunk* menuClick = nullptr;
Mix_Chunk* newLevel = nullptr;

Manager manager;
Dungeon* dGen = new Dungeon(10);
TileMap* map = nullptr;

auto player = new Player();
auto bootIcon = new Object();

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
	groupMenu,
	groupColliders,
	groupScore
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

//Implementation
void Game::StartGame()
{

	player = new Player();
	player->CreatePlayer(400, 300, 3);
	player->entity->addGroup(groupPlayers);

	auto heart1 = new PlayerHeart(12, 12, &player->entity->getComponent<PlayerComponent>(), 1);
	heart1->entity->addGroup(groupForeground);

	auto heart2 = new PlayerHeart(60, 12, &player->entity->getComponent<PlayerComponent>(), 2);
	heart2->entity->addGroup(groupForeground);

	auto heart3 = new PlayerHeart(108, 12, &player->entity->getComponent<PlayerComponent>(), 3);
	heart3->entity->addGroup(groupForeground);

	auto wall1 = new Wall(204, 120, 432, 24, "Assets/WallTexture.png");
	wall1->entity->addGroup(groupForeground);

	auto wall2 = new Wall(204, 528, 432, 24, "Assets/WallTexture.png");
	wall2->entity->addGroup(groupForeground);

	auto wall3 = new Wall(612, 120, 24, 432, "Assets/WallTexture.png");
	wall3->entity->addGroup(groupForeground);

	auto wall4 = new Wall(204, 120, 24, 432, "Assets/WallTexture.png");
	wall4->entity->addGroup(groupForeground);

	auto tens = new Object();
	tens->CreateObject();
	tens->entity->addComponent<TransformComponent>(359,12,24,24,2);
	tens->entity->addComponent<SpriteComponent>("Assets/0.png");
	tens->entity->addComponent<ScoreComponent>("tens");
	tens->entity->addGroup(groupScore);

	auto ones = new Object();
	ones->CreateObject();
	ones->entity->addComponent<TransformComponent>(409, 12, 24, 24, 2);
	ones->entity->addComponent<SpriteComponent>("Assets/0.png");
	ones->entity->addComponent<ScoreComponent>("ones");
	ones->entity->addGroup(groupScore);

	dGen = new Dungeon(99);
	dGen->GenerateLayout();
	dGen->DrawCurrentRoom();


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

		gameRef = this->GetGameReference();

		SDL_SetWindowIcon(window, IMG_Load("Assets/Bucket Knight Icon.png"));

		Mix_Init(MIX_INIT_MP3);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		music = Mix_LoadMUS("Assets/Cruising for Goblins.mp3");

		if (music == NULL) 
		{ 
			std::cout << "Failed to Load Music -> ";
			std::cout << Mix_GetError() << std::endl;
			Mix_ClearError();
		}
		else
		{
			std::cout << "Loaded 'Cruising for Goblins.mp3' by Kevin MacLeod" << std::endl;
		}

		Mix_PlayMusic(music, -1);
		Mix_VolumeMusic(3.5f);

		shoot = Mix_LoadWAV("Assets/shoot.wav");
		shoot->volume = 3;

		enemyHit = Mix_LoadWAV("Assets/enemyHit.wav");
		enemyHit->volume = 3.5f;

		playerHit = Mix_LoadWAV("Assets/playerHit.wav");
		playerHit->volume = 4.5f;

		menuClick = Mix_LoadWAV("Assets/menuClick.wav");
		menuClick->volume = 3;

		newLevel = Mix_LoadWAV("Assets/newLevel.wav");
		newLevel->volume = 3;

		if (newLevel == NULL || menuClick == NULL || playerHit == NULL || enemyHit == NULL || shoot == NULL)
		{
			std::cout << "Failed to Load SFX -> ";
			std::cout << Mix_GetError() << std::endl;
			Mix_ClearError();
		}

		EndGame();
	}

	else
	{
		isRunning = false;
	}

}

auto& background(manager.getGroup(groupBackground));
auto& foreground(manager.getGroup(groupForeground));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& bullets(manager.getGroup(groupBullets));
auto& menu(manager.getGroup(groupMenu));
auto& score(manager.getGroup(groupScore));

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
		if (SDL_BUTTON_LEFT == Game::event.button.button && gameStarted)
		{
			Vector2D dir{ (float)MouseX - player->GetTransform().position.x, (float)MouseY- player->GetTransform().position.y };
			dir = dir.normalize(dir);
			auto bullet = new Bullet();
			bullet->CreateBullet(player->GetTransform().position.x, player->GetTransform().position.y, 12, 12, "Assets/Bullet.png", "playerbullet", dir, 3, 1, 400);
			bullet->entity->addGroup(groupBullets);
			Mix_PlayChannel(-1, shoot, 0);
		}
	}

	if (Game::event.type == SDL_MOUSEBUTTONUP)
	{
		if (SDL_BUTTON_LEFT == Game::event.button.button)
		{
			
		}
	}

	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_SPACE:
			break;

		default:
			break;
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

void Game::update()
{
	manager.refresh();

	if (enemies.size() <= 0 && gameStarted)
	{

		dGen->currentRoom += 1;

		Mix_PlayChannel(-1, newLevel, 0);
		
		for (auto& b : bullets) { b->destroy(); }
		for (auto& e : enemies)
		{
			if (!e->isActive())
			{
				e->delGroup(groupEnemies);
				e->destroy();
			}
		}
		for (auto& s : score)
		{
			if (s->hasComponent<ScoreComponent>())
			{
				s->getComponent<ScoreComponent>().IncrementScore();
				s->getComponent<ScoreComponent>().DisplayScore();
			}
		}
		player->entity->getComponent<TransformComponent>().position = Vector2D(300, 240);
		dGen->DrawCurrentRoom();
	}
	
	if (gameStarted) 
	{

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
				
				if (p->hasComponent<PlayerComponent>())
				{
					if (p->getComponent<PlayerComponent>().canPlayerBeHit())
					{
						for (auto& f : foreground)
						{
							if (f->hasComponent<HeartComponent>())
							{
								f->getComponent<HeartComponent>().Inv = false;
							}
						}
					}
				}

			}
			for (auto& e : enemies)
			{
				if (e->hasComponent<ColliderComponent>())
				{
					if (cc->tag == "playerbullet" && Collision::AABB(e->getComponent<ColliderComponent>(), *cc))
					{
						if (!cc->entity->getComponent<ProjectileComponent>().hit)
						{
							e->getComponent<MeleeEnemy>().hit();
							Mix_PlayChannel(-1, enemyHit, 0);
							cc->entity->getComponent<ProjectileComponent>().hit = true;
						}
					}

					if (cc->tag == "player" && Collision::AABB(e->getComponent<ColliderComponent>(), *cc))
					{
						if (cc->entity->getComponent<PlayerComponent>().canPlayerBeHit())
						{
							Mix_PlayChannel(-1, playerHit, 0);
						}

						cc->entity->getComponent<PlayerComponent>().hit(e);

						for (auto& f : foreground)
						{
							if (f->hasComponent<HeartComponent>())
							{
								f->getComponent<HeartComponent>().Inv = true;
							}
						}
					}
				}
			}
			for (auto& b : bullets)
			{
				if (Collision::AABB(b->getComponent<ColliderComponent>(), *cc) && (cc->tag == "wall"))
				{
					b->getComponent<ProjectileComponent>().hit = true;
				}
				
				if (b->getComponent<ProjectileComponent>().hit)
				{
					b->destroy();
				}
			}
		}
	}

	for (auto& m : menu)
	{
		if (Game::event.type == SDL_MOUSEBUTTONDOWN && m->getComponent<ColliderComponent>().tag == "Play Button" && Collision::AABB(m->getComponent<ColliderComponent>().collider, SDL_Rect { MouseX, MouseY, 1, 1 }) && !gameStarted)
		{
			StartGame();
			gameStarted = true;
			std::cout << "Game Started" << std::endl;
			
			Mix_PlayChannel(-1, menuClick, 0);

			for (auto& m : menu)
			{
				m->destroy();
			}
		}
		else if (Game::event.type == SDL_MOUSEBUTTONDOWN && m->getComponent<ColliderComponent>().tag == "How To Play Button" && Collision::AABB(m->getComponent<ColliderComponent>().collider, SDL_Rect { MouseX, MouseY, 1, 1 }) && !gameStarted)
		{
			for (auto& m : menu)
			{
				m->destroy();
			}
			HowToPlay();
			Mix_PlayChannel(-1, menuClick, 0);
			std::cout << "How to Play Screen Loaded" << std::endl;
		}
		else if (Game::event.type == SDL_MOUSEBUTTONDOWN && m->getComponent<ColliderComponent>().tag == "Back Button" && Collision::AABB(m->getComponent<ColliderComponent>().collider, SDL_Rect { MouseX, MouseY, 1, 1 }) && !gameStarted)
		{
			std::cout << "Back Button Pressed" << std::endl;
			for (auto& m : menu)
			{
				m->destroy();
			}
			EndGame();
			Mix_PlayChannel(-1, menuClick, 0);
			
		}
	
	}
	
	manager.update();
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
	for (auto& m : menu)
	{
		m->draw();
	}
	for (auto& s : score)
	{
		s->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_FreeMusic(music);
	Mix_FreeChunk(shoot);
	Mix_FreeChunk(playerHit);
	Mix_FreeChunk(enemyHit);
	Mix_FreeChunk(menuClick);
	Mix_FreeChunk(newLevel);
	Mix_CloseAudio();
	Mix_Quit();
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
	for (auto& i : oldtiles)
	{
		i->destroy();
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
	auto p = player->entity->getComponent<TransformComponent>();

	for (int i = 0; i < this->numberOfEnemies; i++)
	{
		x = (rand() % (568 - 385)) + 385;
		y = (rand() % (478 - 140)) + 140;

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

void PlayerComponent::StopGame()
{
	gameRef->GetGameReference()->gameStarted = false;
	std::cout << "Game Ended" << std::endl;
	this->entity->destroy();
	Game::EndGame();
}

// Implementation
void Game::EndGame()
{
	background.clear();
	enemies.clear();
	foreground.clear();
	bullets.clear();
	menu.clear();
	players.clear();
	score.clear();

	auto logo = new Trigger(328, 48, 72, 72, 2, "Assets/Bucket Knight Logo.png", "Logo");
	logo->entity->addGroup(groupMenu);

	auto creator = new Trigger(210, 456, 387, 25, 1, "Assets/Creator.png", "Created By");
	creator->entity->addGroup(groupMenu);

	auto kevin = new Trigger(272, 500, 269, 25, 1, "Assets/Kevin.png", "Kevin");
	kevin->entity->addGroup(groupMenu);

	auto jsfxr = new Trigger(303, 546, 215, 25, 1, "Assets/jsfxr.png", "jsfxr");
	jsfxr->entity->addGroup(groupMenu);

	auto playButton = new Trigger(152, 200, 256, 48, 2, "Assets/PlayButton.png", "Play Button");
	playButton->entity->addGroup(groupMenu);

	auto howButton = new Trigger(152, 320, 256, 48, 2, "Assets/HowToPlayButton.png", "How To Play Button");
	howButton->entity->addGroup(groupMenu);

}

void Game::HowToPlay()
{
	auto backButton = new Trigger(24, 512, 100, 27, 2, "Assets/Back.png", "Back Button");
	backButton->entity->addGroup(groupMenu);

	auto howtoplayscreen = new Trigger(0, 0, 204, 156, 4, "Assets/HowToPlayScreen.png", "howtoplay Sprite");
	howtoplayscreen->entity->addGroup(groupMenu);
}