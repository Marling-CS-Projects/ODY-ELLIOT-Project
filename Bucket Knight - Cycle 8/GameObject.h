#pragma once
#include "Game.h"
#include "ECS.h"

class GameObject
{

public:
	GameObject();
	~GameObject();

	Entity* gameObject;
};
