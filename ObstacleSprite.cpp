#include "Sprites.h"
#include "Game.h"

const int obstacleVelocity = -15;

void DyingTree1::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Sh*t! caught in the Dying Trees!\nWriggle out for your next run?");

	setSrcRect(0, 0, 32, 32);
	setTransform(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void DyingTree1::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mPosition.x <= Game::SCREEN_WIDTH + 101) {
		rTransform.mVelocity.x = obstacleVelocity;

		getCollider().setColliderRect(0, rTransform.mPosition.x + 89, rTransform.mPosition.y + 8, 166, 264);
	}
	if (rTransform.mPosition.x <= -rTransform.mWidth) rTransform.mVelocity.zero();
}



void DyingTree2::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Sh*t! caught in the Dying Trees!\nWriggle out for your next run?");
	

	setSrcRect(32, 0, 32, 32);
	setTransform(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void DyingTree2::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mPosition.x <= Game::SCREEN_WIDTH + 101) {
		rTransform.mVelocity.x = obstacleVelocity;

		getCollider().setColliderRect(0, rTransform.mPosition.x + 72, rTransform.mPosition.y + 93, 140, 187);
	}
	if (rTransform.mPosition.x <= -rTransform.mWidth) rTransform.mVelocity.zero();
}



void Bucket::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Danmit! You've kicked The Bucket\nDid I mention you have nine (ahem) lives?");

	setSrcRect(64, 0, 32, 32);
	setTransform(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void Bucket::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mPosition.x <= Game::SCREEN_WIDTH + 101) {
		rTransform.mVelocity.x = obstacleVelocity;

		getCollider().setColliderRect(0, rTransform.mPosition.x + 105, rTransform.mPosition.y + 51, 106, 221);
	}
	if (rTransform.mPosition.x <= -rTransform.mWidth) rTransform.mVelocity.zero();
}



void TreeStump::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Oof! crashed right into a Tree Stump!\nWatch your path, Rex!");

	setSrcRect(0, 32, 32, 32);
	setTransform(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void TreeStump::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mPosition.x <= Game::SCREEN_WIDTH + 101) {
		rTransform.mVelocity.x = obstacleVelocity;

		getCollider().setColliderRect(0, rTransform.mPosition.x + 123, rTransform.mPosition.y + 162, 81, 110);
	}
	if (rTransform.mPosition.x <= -rTransform.mWidth) rTransform.mVelocity.zero();
}



void Stalker::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Hehe, the one-eyed Stalker...\nLook away next time, okay?");

	setAnimation(1, 2, 200);
	setSrcRect(32, 32, 32, 32);
	setTransform(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void Stalker::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mPosition.x <= Game::SCREEN_WIDTH + 101) {
		rTransform.mVelocity.x = obstacleVelocity;

		getCollider().setColliderRect(0, rTransform.mPosition.x + 115, rTransform.mPosition.y + 8, 123, 255);
	}
	if (rTransform.mPosition.x <= -rTransform.mWidth) rTransform.mVelocity.zero();

	rSrcRect.x = 32 + (rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount()));
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}



void Brute::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Ouch, crushed by the merciless Brute!\nOh well, you're not THAT hurt, go again?");

	setAnimation(2, 2, 200);
	setSrcRect(0, 64, 32, 32);
	setTransform(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 355, 273, 275);
}

void Brute::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mPosition.x <= Game::SCREEN_WIDTH + 101) {
		rTransform.mVelocity.x = obstacleVelocity;

		getCollider().setColliderRect(0, rTransform.mPosition.x + 72, rTransform.mPosition.y + 59, 191, 213);
	}

	if (rTransform.mPosition.x <= -rTransform.mWidth) rTransform.mVelocity.zero();

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}


void StalkerPup::init() {
	auto upmiddown = std::rand() % 15;

	setAnimation(3, 2, 200);
	setSrcRect(0, 96, 32, 32);
	
	getCollider().resize(1);
	getCollider().setCollisionTag("Yikes, Stalker Pups...\nNothing to see or say here, Rex, run again?");

	if (upmiddown <= 5) {
		setTransform(Game::SCREEN_WIDTH + 102, 150, 173, 175);
	}
	else if (upmiddown > 6 <= 10) {
		setTransform(Game::SCREEN_WIDTH + 102, 280, 173, 175);
	}
	else {
		setTransform(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 300, 173, 175);
	}
}

void StalkerPup::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mPosition.x <= Game::SCREEN_WIDTH + 101) {
		rTransform.mVelocity.x = obstacleVelocity;

		getCollider().setColliderRect(0, rTransform.mPosition.x + 64, rTransform.mPosition.y, 109, 175);
	}

	if (rTransform.mPosition.x <= -rTransform.mWidth) rTransform.mVelocity.zero();


	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}



void Gale::init() {
	auto upmiddown = std::rand() % 15;

	setAnimation(4, 2, 200);
	setSrcRect(0, 128, 32, 32);

	getCollider().resize(1);
	getCollider().setCollisionTag("Whoaa, you let the Night Gale sweep you away?\nHold on tight next run!");

	if (upmiddown <= 5) {
		setTransform(Game::SCREEN_WIDTH + 102, 150, 173, 175);
	}
	else if (upmiddown > 6 <= 10) {
		setTransform(Game::SCREEN_WIDTH + 102, 280, 173, 175);
	}
	else {
		setTransform(Game::SCREEN_WIDTH + 102, Game::SCREEN_HEIGHT - 300, 173, 175);
	}
}

void Gale::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mPosition.x <= Game::SCREEN_WIDTH + 101) {
		rTransform.mVelocity.x = obstacleVelocity;

		getCollider().setColliderRect(0, rTransform.mPosition.x + 64, rTransform.mPosition.y, 109, 175);
	}

	if (rTransform.mPosition.x <= -rTransform.mWidth) rTransform.mVelocity.zero();

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}