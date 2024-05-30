#include <memory>

#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "KeyboardController.h"
#include "Sprites.h"

SpriteComponent::SpriteComponent(const char* pathToTexture, std::unique_ptr<Sprite> sp, bool isAnimated, int x, int y, int w, int h)
	: sprite(std::move(sp))
{
	sprite->animated = isAnimated;
	sprite->srcRect.x = x;
	sprite->srcRect.y = y;
	sprite->srcRect.h = h;
	sprite->srcRect.w = w;

	setTexture(pathToTexture);
}

SpriteComponent::~SpriteComponent() {
	SDL_DestroyTexture(sprite->texture);
}

void SpriteComponent::setTexture(const char* pathToTexture) const {
	sprite->pathToTexture = const_cast<char*>(pathToTexture);
	sprite->texture = TextureManager::loadTexture(pathToTexture);
}

void SpriteComponent::init() {
	if (!entity->hasComponent<TransformComponent>()) {
		entity->addComponent<TransformComponent>();
	}

	sprite->transform = &entity->getComponent<TransformComponent>();

	sprite->init();
}

void SpriteComponent::update() {
	sprite->update();

	sprite->destRect.x = static_cast<int>(sprite->transform->position.x);
	sprite->destRect.y = static_cast<int>(sprite->transform->position.y);
	sprite->destRect.w = sprite->transform->width;
	sprite->destRect.h = sprite->transform->height;
}

void SpriteComponent::draw() {
	TextureManager::draw(sprite->pathToTexture, sprite->texture, sprite->srcRect, sprite->destRect);
}