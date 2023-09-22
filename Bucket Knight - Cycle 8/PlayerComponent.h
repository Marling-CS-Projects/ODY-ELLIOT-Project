#pragma once
#include "Components.h"
#include <SDL_mixer.h>

class PlayerComponent : public Component
{

public:

	PlayerComponent(int health, int cooldownTime)
	{
		this->health = health;
		this->InvCooldown = cooldownTime;
		canBeHit = true;
	}

	~PlayerComponent()
	{
		entity->destroy();
	}
	
	void StopGame();

	void update() override
	{
		if (health < 1)
		{
			StopGame();
		}
		else if (InvFrame <= frames)
		{
			canBeHit = true;
		}

		if (RolFrame <= frames)
		{
			rolling = false;
		}

		if (rolling)
		{
			this->entity->getComponent<TransformComponent>().speed = 7;
		}
		else
		{
			this->entity->getComponent<TransformComponent>().speed = 3;
		}

		frames += 1;
	}

	void hit(Entity * enemy)
	{
		if (canBeHit)
		{
			health -= 1;
			canBeHit = false;
			InvFrame = frames + InvCooldown;
		}
	}

	void roll(Mix_Chunk* r)
	{
		if (!rolling && RolUseAgainFrame <= frames && (entity->getComponent<TransformComponent>().velocity.x != 0 || entity->getComponent<TransformComponent>().velocity.y != 0))
		{
			RolFrame = frames + RolAbilityTime;
			RolUseAgainFrame = RolFrame + RolCooldown;
			std::cout << "Player Rolled" << std::endl;
			Mix_PlayChannel(-1, r, 0);
			rolling = true;
		}
	}

	bool canRoll()
	{
		return (RolUseAgainFrame <= frames);
	}
	
	bool canPlayerBeHit()
	{
		return canBeHit;
	}

	int health;

private:
	bool canBeHit;
	bool rolling = false;
	int frames;
	int InvCooldown;
	int InvFrame;
	int RolAbilityTime = 10;
	int RolCooldown = 110;
	int RolFrame;
	int RolUseAgainFrame;
};