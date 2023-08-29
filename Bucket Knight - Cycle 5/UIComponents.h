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

private:

	PlayerComponent * player;
	int pos;

};

class ScoreComponent : public Component
{
public:

	ScoreComponent(SpriteComponent* tens, SpriteComponent* ones)
	{
		this->score = 0;
	}

	int GetScore()
	{
		return this->score;
	}

	void IncrementScore()
	{
		this->score += 1;
	}
	
	void DisplayScore();
	
	void update() override
	{
		string s = (char*)score;
		if (score < 10)
		{
			tens->setTex("Assets/0.png");
		}
		else if (score > 99)
		{
			return; // makes it so it doesnt break
		}
		else
		{
			tens->setTex("Assets/" + s.at(0) + '.png');
		}

		ones->setTex("Assets/" + s.at(1) + '.png');
	}

private:
	int score;
	SpriteComponent* tens;
	SpriteComponent* ones;
};