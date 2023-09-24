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
		else if (!Inv)
		{
			this->entity->getComponent<SpriteComponent>().setTex("Assets/HeartON.png");
		}
		else
		{
			this->entity->getComponent<SpriteComponent>().setTex("Assets/HeartInv.png");
		}
	}

	bool Inv = false;

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

		if (column == "hundreds")
		{
			int i = (score - (score - (score % 10)) - (score % 10)) / 10;
			string s = "Assets/" + to_string(i) + ".png";
			const char* c = s.c_str();
			sprite->setTex(c);
		}
		else if (column == "tens")
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

class RollIcon : public Component
{
public:
	bool on = true;

	void update() override
	{
		if (on)
		{
			this->entity->getComponent<SpriteComponent>().setTex("Assets/DashIcon.png");
		}
		else
		{
			this->entity->getComponent<SpriteComponent>().setTex("Assets/DashIconOFF.png");
		}
	}
};

class CanShootIcon : public Component
{
public:
	bool on = true;

	CanShootIcon(string name)
	{
		this->name = name;
	}

	void update() override
	{
		if (on && (name == "Magic" || name == "Gun"))
		{
			this->entity->getComponent<SpriteComponent>().setTex(("Assets/" + name + "ON.png").c_str());
		}
		else if (name == "Magic" || name == "Gun")
		{
			this->entity->getComponent<SpriteComponent>().setTex(("Assets/" + name + "OFF.png").c_str());
		}
		else if (on)
		{
			this->entity->getComponent<SpriteComponent>().setTex("Assets/MeleeON.png");
		}
		else
		{
			this->entity->getComponent<SpriteComponent>().setTex("Assets/MeleeOFF.png");
		}
	}

private:
	string name;

};