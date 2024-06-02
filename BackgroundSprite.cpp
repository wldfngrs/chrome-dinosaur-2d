#include "Sprites.h"

void Background::init() {
	if (animated) {
		setAnimation(0, 2, 500);
	}
}

void Background::update() {
	if (animated) {
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount);
		srcRect.y = animIndex * srcRect.h;
	}
}

void CelestialBody::update() {
	transform->velocity.x = -1;

	if (transform->position.x <= -transform->width) {
		transform->position.x = Game::SCREEN_WIDTH;
	}
}

void Ground::init() {
	setAnimation(0, 3, 200);
}

void Ground::update() {
	if (animated) {
		srcRect.y = srcRect.h * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount);
		srcRect.x = animIndex * srcRect.w;
	}
}