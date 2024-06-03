#include "Sprites.h"
#include "Game.h"

void DyingTree1::init() {
	transform->entity->collidable = true;
	mColliders.resize(2);

	setSrcRect(0, 0, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
}

void DyingTree1::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = -12;

		setCollider(0, transform->position.x + 2, transform->position.y + 2, 23, 7);
		setCollider(1, transform->position.x + 9, transform->position.y + 16, 13, 12);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void DyingTree2::init() {
	transform->entity->collidable = true;
	mColliders.resize(2);

	setSrcRect(32, 0, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
}

void DyingTree2::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = -12;

		setCollider(0, transform->position.x + 1, transform->position.y + 31, 4, 3);
		setCollider(1, transform->position.x + 9, transform->position.y + 9, 10, 22);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void Bucket::init() {
	transform->entity->collidable = true;
	mColliders.resize(1);

	setSrcRect(64, 0, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
}

void Bucket::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = -12;

		setCollider(0, transform->position.x + 7, transform->position.y + 6, 17, 25);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void TreeStump::init() {
	transform->entity->collidable = true;
	mColliders.resize(1);

	setSrcRect(0, 32, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
}

void TreeStump::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = -12;

		setCollider(0, transform->position.x + 7, transform->position.y + 19, 16, 12);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void Stalker::init() {
	transform->entity->collidable = true;
	mColliders.resize(3);

	setAnimation(1, 2, 200);
	setSrcRect(32, 32, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
}

void Stalker::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = -12;

		setCollider(0, transform->position.x + 5, transform->position.y + 7, 6, 11);
		setCollider(1, transform->position.x + 8, transform->position.y + 32, 7, 8);
		setCollider(2, transform->position.x + 35, transform->position.y + 35, 8, 3);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();

	srcRect.x = 32 + (srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount));
	srcRect.y = animIndex * srcRect.h;
}



void Brute::init() {
	transform->entity->collidable = true;
	mColliders.resize(2);

	setAnimation(2, 2, 200);
	setSrcRect(0, 64, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
}

void Brute::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = -12;
		
		setCollider(0, transform->position.x + 2, transform->position.y + 14, 27, 7);
		setCollider(1, transform->position.x + 8, transform->position.y + 7, 15, 5);
	}

	if (transform->position.x <= -transform->width) transform->velocity.zero();

	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount);
	srcRect.y = animIndex * srcRect.h;
}


void StalkerPup::init() {
	transform->entity->collidable = true;

	auto upordown = std::rand() % 10;

	setAnimation(3, 2, 200);
	setSrcRect(0, 96, 32, 32);
	
	mColliders.resize(2);

	if (upordown >= 5) {
		//setDestRect(Game::SCREEN_WIDTH + 102, 185, 103, 100);
		setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
	}
	else {
		//setDestRect(Game::SCREEN_WIDTH + 102, 295, 103, 100);
		setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
	}
}

void StalkerPup::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = -12;

		setCollider(0, transform->position.x + 2, transform->position.y + 14, 8, 9);
		setCollider(1, transform->position.x + 5, transform->position.y + 9, 25, 9);
	}

	if (transform->position.x <= -transform->width) transform->velocity.zero();


	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount);
	srcRect.y = animIndex * srcRect.h;
}



void Gale::init() {
	transform->entity->collidable = true;

	auto upordown = std::rand() % 10;

	setAnimation(4, 2, 200);
	setSrcRect(0, 128, 32, 32);

	mColliders.resize(4);

	if (upordown >= 5) {
		//setDestRect(Game::SCREEN_WIDTH + 102, 135, 153, 150);
		setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
	}
	else {
		//setDestRect(Game::SCREEN_WIDTH + 102, 245, 153, 150);
		setDestRect(Game::SCREEN_WIDTH + 102, 225, 173, 175);
	}
}

void Gale::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = -12;

		setCollider(0, transform->position.x + 2, transform->position.y + 32, 5, 8);
		setCollider(1, transform->position.x + 6, transform->position.y + 4, 8, 11);
		setCollider(2, transform->position.x + 11, transform->position.y + 33, 16, 8);
		setCollider(3, transform->position.x + 21, transform->position.y + 26, 7, 3);
	}

	if (transform->position.x <= -transform->width) transform->velocity.zero();

	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount);
	srcRect.y = animIndex * srcRect.h;
}