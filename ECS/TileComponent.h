#pragma once

#include "Components.h"
#include "SDL.h"

class TileComponent : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite = nullptr;

	SDL_Rect tileRect;
	int tileID;
	char* path = nullptr;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;

		tileID = id;

		switch (tileID) {
		case 0:
			break;
		case 1:
			path = const_cast<char*>("assets\\Classic\\cloud_day.png");
			break;
		default:
			break;
		}
	}

	~TileComponent() {}

	void init() override {
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};