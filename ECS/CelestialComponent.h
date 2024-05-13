#pragma once

#include "Components.h"

class CelestialComponent : public Component {
	TransformComponent* transform;
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	CelestialComponent(const char* pathToTexture) {
		setTexture(pathToTexture);
	}

	~CelestialComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* pathToTexture) {
		texture = TextureManager::loadTexture(pathToTexture);
	}

	void init() override {
		srcRect.x = srcRect.y = 0;
		destRect.x = 900;
		destRect.y = 100;

		srcRect.w = destRect.w = 60;
		srcRect.h = destRect.h = 54;
	}

	void update() override {
		destRect.x--;
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);

		if (destRect.x < -60) {
			destRect.x = 900;
		}
	}
};