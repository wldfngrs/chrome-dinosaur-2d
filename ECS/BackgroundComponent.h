#pragma once

#include "SDL.h"
#include "Components.h"

class BackgroundComponent : public Component {
	Vector2D velocity;
	SDL_Rect srcRect, destRect;

	bool animated;
	int frames;
	int speed;

	SDL_Texture* texture;

public:
	BackgroundComponent(const char* pathToTexture) {
		setTexture(pathToTexture);
	}
	
	BackgroundComponent(const char* pathToTexture, int nFrames, int mSpeed) {
		animated = true;
		frames = nFrames;
		speed = mSpeed;
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

		destRect.w = 900;
		destRect.h = 400;

		srcRect.h = 64;
		srcRect.w = 96;

		velocity.zero();
	}

	void update() override {
		//bg = TextureManager::loadTexture(pathToTexture);
		/* check the level of the player and update the background as required*/
		/* check the velocity of the background and update the background sub-tiles as required (rainfall, frostfall,
		   leaves dropping etc) */
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}
};