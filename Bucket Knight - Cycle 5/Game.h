#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "ECS.h"

class ColliderComponent;

class Game
{

public:
	Game(Game* game);
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; };

	static void AddTile(int id, int x, int y);
	static void AddEntity();
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

	void windowMousePositionToLogicalMousePosition(SDL_Renderer* renderer, SDL_Window* window, int realMouseX, int realMouseY);

	void AddFrame()
	{
		frames += 1;
	}

	int GetFrames()
	{
		return frames;
	}

	Game* GetGameReference()
	{
		return game;
	}

	const void RemoveEnemyGroup(Entity* entity);
	

private:
	bool isRunning;
	SDL_Window *window;

	int cnt = 0;
	int frames = 0;
	Game* game;

};

