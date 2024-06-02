#include "Sprites.h"
#include "Game.h"

void DyingTree1::init() {
	transform->entity->collidable = true;
}

void DyingTree1::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) transform->velocity.x = -10;
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void DyingTree2::init() {
	transform->entity->collidable = true;
}

void DyingTree2::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) transform->velocity.x = -10;
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void Bucket::init() {
	transform->entity->collidable = true;
}

void Bucket::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) transform->velocity.x = -10;
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void TreeStump2::init() {
	transform->entity->collidable = true;
}

void TreeStump2::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) transform->velocity.x = -10;
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void Stalker::init() {
	transform->entity->collidable = true;

	setAnimation(1, 2, 200);
}

void Stalker::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) transform->velocity.x = -10;
	if (transform->position.x <= -transform->width) transform->velocity.zero();

	srcRect.x = 32 + (srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount));
	srcRect.y = animIndex * srcRect.h;
}



void Brute::init() {
	transform->entity->collidable = true;

	setAnimation(2, 2, 200);
}

void Brute::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) transform->velocity.x = -10;
	if (transform->position.x <= -transform->width) transform->velocity.zero();

	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount);
	srcRect.y = animIndex * srcRect.h;
}


void StalkerPup::init() {
	transform->entity->collidable = true;

	setAnimation(3, 2, 200);
}

void StalkerPup::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) transform->velocity.x = -10;
	if (transform->position.x <= -transform->width) transform->velocity.zero();

	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount);
	srcRect.y = animIndex * srcRect.h;
}



void Gale::init() {
	transform->entity->collidable = true;

	setAnimation(4, 2, 200);
}

void Gale::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) transform->velocity.x = -10;
	if (transform->position.x <= -transform->width) transform->velocity.zero();

	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount);
	srcRect.y = animIndex * srcRect.h;
}