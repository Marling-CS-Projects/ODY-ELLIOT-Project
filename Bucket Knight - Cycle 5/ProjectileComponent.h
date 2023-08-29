#pragma once
#include "Components.h"

class ProjectileComponent : public Component
{

public:
	ProjectileComponent(float speed, int damage, float distance, Vector2D direction)
	{
		this->speed = speed;
		this->damage = damage;
		this->distance = distance;
		this->direction = direction;
	}

	~ProjectileComponent()
	{
		entity->destroy();
	}

	void init() override
	{
		transform = &this->entity->getComponent<TransformComponent>();
		transform->speed = this->speed;
		transform->velocity = direction;
	}

	void update() override
	{
		distance -= speed;

		if (distance <=  0)
		{
			this->~ProjectileComponent();
		}
	}

private:

	float distance;
	float speed;
	float damage;
	Vector2D direction;
	TransformComponent * transform;

};