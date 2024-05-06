#pragma once

#include "Components.h"
#include "SDL.h"

class TileComponent : public Component {
public:
	TransformComponent transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id) {
	
	}
};