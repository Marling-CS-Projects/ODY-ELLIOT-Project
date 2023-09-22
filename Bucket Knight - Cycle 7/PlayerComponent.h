#pragma once
#include "Components.h"

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
	
	bool canPlayerBeHit()
	{
		return canBeHit;
	}

	int health;

private:
	bool canBeHit;
	int frames;
	int InvCooldown;
	int InvFrame;
};