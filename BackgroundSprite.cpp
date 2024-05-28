#include "Sprites.h"

void BackgroundSprite::init() {
	if (animated) setAnimation(0, 2, 500);
}

void BackgroundSprite::update() {
	if (animated) {
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		srcRect.y = animIndex * srcRect.h;
	}
}

void CelestialBodySprite::update() {
	transform->position.x--;

	if (transform->position.x <= -transform->width) {
		transform->position.x = Game::SCREEN_WIDTH;
	}
}

void GroundSprite::init() {
	setAnimation(0, 3, 200);
}

void GroundSprite::update() {
	if (animated) {
		srcRect.y = srcRect.h * static_cast<int>((SDL_GetTicks() / speed) % frames);
		srcRect.x = animIndex * srcRect.w;
	}
}