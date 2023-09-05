#pragma once

#include "Components.h"
#include <iostream>

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

	ScoreComponent(string column) // column can be tens or ones
	{
		this->score = 0;
		this->column = column;
	}

	int GetScore()
	{
		return this->score;
	}

	void IncrementScore()
	{
		score += 1;
	}
	
	void DisplayScore()
	{

		if (column == "tens")
		{
			int i = (score - (score % 10)) / 10;
			string s = "Assets/" + to_string(i) + ".png";
			const char* c = s.c_str();
			sprite->setTex(c);
		}
		else if (column == "ones")
		{
			int i = score % 10;
			string s = "Assets/" + to_string(i) + ".png";
			const char* c = s.c_str();
			sprite->setTex(c);
		}
	}
	
	void init() override
	{
		if (entity->hasComponent<SpriteComponent>())
		{
			this->sprite = &entity->getComponent<SpriteComponent>();
		}
		else
		{
			std::cout << "Error: No Sprite Component attatched to the Score Entity" << std::endl;
		}
	}

private:
	int score = 0;
	string column;
	SpriteComponent* sprite;
};