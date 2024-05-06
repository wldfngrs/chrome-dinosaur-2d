#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component {
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* pathToTexture) {
		setTexture(pathToTexture);
	}
	
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* pathToTexture) {
		texture = TextureManager::loadTexture(pathToTexture);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		destRect.h = /*110*/ transform->width;
		destRect.w = /*100*/ transform->height;
		destRect.x = 60;
		destRect.y = 310;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = destRect.w * 2;
		srcRect.h = destRect.h * 2;
	}

	void update() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width;
		destRect.h = transform->height;
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}
};