#include "Game.h"

Game* game = nullptr;

int main(int argc, char *arg[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game(game);

	game->init("Bucket Knight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 816, 624, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) 
		{
			SDL_Delay(frameDelay - frameTime);
		}

		game->AddFrame();
		//std::cout << game.GetFrames() << std::endl;
	}

	game->clean();

	return 0;
}
