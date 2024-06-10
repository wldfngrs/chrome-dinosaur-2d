#include "Sprites.h"
#include "Game.h"

const int obstacleVelocity = -15;

void DyingTree1::init() {
	transform->entity->collidable = true;
	collider.colliderRects.resize(1);
	collider.tagOnCollision = "Sh*t! caught in the Dying Trees!";

	setSrcRect(0, 0, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void DyingTree1::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = obstacleVelocity;

		setCollider(0, transform->position.x + 89, transform->position.y + 8, 166, 264);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void DyingTree2::init() {
	transform->entity->collidable = true;
	collider.colliderRects.resize(1);
	collider.tagOnCollision = "Sh*t! caught in the Dying Trees! Wriggle out for your next run?";
	

	setSrcRect(32, 0, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void DyingTree2::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = obstacleVelocity;

		setCollider(0, transform->position.x + 72, transform->position.y + 93, 140, 187);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void Bucket::init() {
	transform->entity->collidable = true;
	collider.colliderRects.resize(1);
	collider.tagOnCollision = "Danmit! You've kicked the Bucket. Did I mention you have nine(ahem) lives?";

	setSrcRect(64, 0, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void Bucket::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = obstacleVelocity;

		setCollider(0, transform->position.x + 105, transform->position.y + 51, 106, 221);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void TreeStump::init() {
	transform->entity->collidable = true;
	collider.colliderRects.resize(1);
	collider.tagOnCollision = "Oof! The Tree Stump ended your run! Watch your path, Rex.";

	setSrcRect(0, 32, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void TreeStump::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = obstacleVelocity;

		setCollider(0, transform->position.x + 123, transform->position.y + 162, 81, 110);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();
}



void Stalker::init() {
	transform->entity->collidable = true;
	collider.colliderRects.resize(1);
	collider.tagOnCollision = "Hehe, the one-eyed wanderer gets us all...burned by the Stalker!";

	setAnimation(1, 2, 200);
	setSrcRect(32, 32, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void Stalker::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = obstacleVelocity;

		setCollider(0, transform->position.x + 115, transform->position.y + 8, 123, 255);
	}
	if (transform->position.x <= -transform->width) transform->velocity.zero();

	srcRect.x = 32 + (srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount));
	srcRect.y = animIndex * srcRect.h;
}



void Brute::init() {
	transform->entity->collidable = true;
	collider.colliderRects.resize(1);
	collider.tagOnCollision = "Ouch, crushed by the merciless Brute! Oh well, you're not THAT hurt, go again?";

	setAnimation(2, 2, 200);
	setSrcRect(0, 64, 32, 32);
	setDestRect(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void Brute::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = obstacleVelocity;

		setCollider(0, transform->position.x + 72, transform->position.y + 59, 191, 213);
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
	
	collider.colliderRects.resize(1);
	collider.tagOnCollision = "Yikes, the baby one-eyed wanderer gets us all...better luck with the Stalker Pup next time!";

	if (upordown >= 5) {
		setDestRect(Game::SCREEN_WIDTH + 102, 280, 173, 175);
	}
	else {
		setDestRect(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 300, 173, 175);
	}
}

void StalkerPup::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = obstacleVelocity;

		setCollider(0, transform->position.x + 64, transform->position.y, 109, 175);
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

	collider.colliderRects.resize(1);
	collider.tagOnCollision = "Whoaa, you let the Night Gale sweep you away? Hold on tight next run!";

	if (upordown >= 5) {
		setDestRect(Game::SCREEN_WIDTH + 102, 280, 173, 175);
	}
	else {
		setDestRect(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 300, 173, 175);
	}
}

void Gale::update() {
	if (transform->position.x <= Game::SCREEN_WIDTH + 101) {
		transform->velocity.x = obstacleVelocity;

		setCollider(0, transform->position.x + 64, transform->position.y, 109, 175);
	}

	if (transform->position.x <= -transform->width) transform->velocity.zero();

	srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / framesSpeed) % framesCount);
	srcRect.y = animIndex * srcRect.h;
}