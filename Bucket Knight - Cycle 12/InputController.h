#pragma once

#include "Game.h"
#include "Components.h"

class InputController : public Component
{
public:
	
	bool w, a, s, d = false;

	TransformComponent* transform;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
	
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				//transform->velocity.y = -1;
				w = true;
				break;
			case SDLK_s:
				//transform->velocity.y = 1;
				s = true;
				break;
			case SDLK_d:
				//transform->velocity.x = 1;
				d = true;
				break;
			case SDLK_a:
				//transform->velocity.x = -1;
				a = true;
				break;

			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				//transform->velocity.y = 0;
				w = false;
				break;
			case SDLK_s:
				//transform->velocity.y = 0;
				s = false;
				break;
			case SDLK_d:
				//transform->velocity.x = 0;
				d = false;
				break;
			case SDLK_a:
				//transform->velocity.x = 0;
				a = false;
				break;

			default:
				break;
			}
		}

		Vector2D dir;

		if (a && d)
		{
			dir.x = 0;
		}
		else if (a)
		{
			dir.x = -1;
		}
		else if (d)
		{
			dir.x = 1;
		}
		else
		{
			dir.x = 0;
		}

		if (w && s)
		{
			dir.y = 0;
		}
		else if (w)
		{
			dir.y = -1;
		}
		else if (s)
		{
			dir.y = 1;
		}
		else
		{
			dir.y = 0;
		}

		//dir = dir.normalize(dir);
		transform->velocity = dir;
	}

	
	
};