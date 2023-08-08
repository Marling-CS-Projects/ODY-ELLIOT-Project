#pragma once

#include "Components.h"

class HeartComponent : public Component
{

public:

	HeartComponent(PlayerComponent *player, int position)
	{
		this->player = player;
		this->pos = position;
	}

	void update() override
	{
		if (player->health < pos)
		{
			this->entity->getComponent<SpriteComponent>().setTex("Assets/HeartOFF.png");
		}
		else
		{
			this->entity->getComponent<SpriteComponent>().setTex("Assets/HeartON.png");
		}
	}

	HeartComponent();

private:

	PlayerComponent * player;
	int pos;

};