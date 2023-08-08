#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height;
	int width;
	float scale;

	float speed = 3;

	TransformComponent()
	{
		position.Zero();

		height = width = 24;
		scale = 1.0f;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;

		this->height = this->width = 24;
		this->scale = 1.0f;
	}

	TransformComponent(float x, float y, int width, int height)
	{
		position.x = x;
		position.y = y;

		this->height = height;
		this->width = width;
		this->scale = 1.0f;
	}

	TransformComponent(float x, float y, int width, int height, float scale)
	{
		position.x = x;
		position.y = y;

		this->height = height;
		this->width = width;
		this->scale = scale;
	}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

};