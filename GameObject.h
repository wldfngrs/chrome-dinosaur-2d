#pragma once

#include "Game.h"

#include <string>

class GameObject {
	int xpos;
	int ypos;

	SDL_Texture* objTexture = nullptr;
	SDL_Rect srcRect, destRect;

public:
	GameObject(const char* pathToTexture, int x, int y);
	~GameObject();

	void update();
	void render();
};