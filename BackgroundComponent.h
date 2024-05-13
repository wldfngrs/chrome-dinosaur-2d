#pragma once

#include "SDL.h"
#include "Components.h"

class BackgroundComponent : public Component {
	Vector2D velocity;
	SDL_Rect srcRect, destRect;

	SDL_Texture* texture;

public:
	BackgroundComponent(const char* pathToTexture) {
		setTexture(pathToTexture);
	}
	
	~BackgroundComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* pathToTexture) {
		texture = TextureManager::loadTexture(pathToTexture);
	}

	void init() override {
		srcRect.x = srcRect.y = 0;
		destRect.x = destRect.y = 0;

		srcRect.w = destRect.w = 900;
		srcRect.h = destRect.h = 400;
	}

	void update() override {
		//bg = TextureManager::loadTexture(pathToTexture);
		/* check the level of the player and update the background as required*/
		/* check the velocity of the background and update the background sub-tiles as required (rainfall, frostfall,
		   leaves dropping etc) */
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}
};