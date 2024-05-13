#pragma once

#include "Components.h"

class GroundComponent : public Component {
	TransformComponent* transform;
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	GroundComponent(const char* pathToTexture) {
		setTexture(pathToTexture);
	}

	GroundComponent(const char* pathToTexture, int nFrames, int mSpeed) {
		animated = true;
		frames = nFrames;
		speed = mSpeed;
		setTexture(pathToTexture);
	}

	~GroundComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* pathToTexture) {
		texture = TextureManager::loadTexture(pathToTexture);
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = 96;
		srcRect.h = 16;
		destRect.x = transform->position.x;
		destRect.y = transform->position.y;

		destRect.w = transform->width;
		destRect.h = transform->height;
	}

	void update() override {
		//bg = TextureManager::loadTexture(pathToTexture);
		/* check the level of the player and update the ground as required */
		if (animated) {
			srcRect.y = srcRect.h * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}
};
