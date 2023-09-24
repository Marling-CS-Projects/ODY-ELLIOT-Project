#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;

		tileID = id;

		switch (tileID)
		{
		case 0:
			path = "Assets/FloorTexture.png";
			break;
		case 1:
			path = "Assets/FloorTexture2.png";
			break;
		case 2:
			path = "Assets/FloorTexture3.png";
			break;
		case 3:
			path = "Assets/FloorTexture4.png";
			break;
		case 4:
			path = "Assets/FloorTexture5.png";
			break;
		case 5:
			path = "Assets/FloorTexture6.png";
			break;
		case 6:
			path = "Assets/FloorTexture7.png";
			break;
		default:
			path = "Assets/FloorTexture.png";
			break;
		}

		
	}

	void init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();

		this->entity->activate();
	}
};