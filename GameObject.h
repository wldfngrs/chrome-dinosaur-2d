#pragma once

#include "Game.h"

#include <string>

class GameObject {
	int xpos;
	int ypos;

	std::string errorMessage;

	SDL_Texture* objTexture = nullptr;
	SDL_Rect srcRect, destRect;

public:
	GameObject(const char* pathToTexture, int x, int y);
	~GameObject();

	std::string getErrorMessage() const;

	void update();
	int render();
};