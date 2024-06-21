#include "Sprites.h"
#include "Game.h"

void DyingTree1::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Sh*t! caught in the Dying Trees!\nWriggle out for your next run?");

	setSrcRect(0, 0, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 102, Game::mSCREEN_HEIGHT - 355, 273, 275);
}

void DyingTree1::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mPosition.x <= Game::mSCREEN_WIDTH + 101) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 89, rTransform.mPosition.y + 8, 166, 264);
	
	}
}



void DyingTree2::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Sh*t! caught in the Dying Trees!\nWriggle out for your next run?");
	

	setSrcRect(32, 0, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 102, Game::mSCREEN_HEIGHT - 355, 273, 275);
}

void DyingTree2::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mPosition.x <= Game::mSCREEN_WIDTH + 101) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 72, rTransform.mPosition.y + 93, 140, 187);
	
	}
}



void Bucket::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Danmit! You've kicked The Bucket\nDid I mention you have nine (ahem) lives?");

	setSrcRect(64, 0, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 102, Game::mSCREEN_HEIGHT - 355, 273, 275);
}

void Bucket::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mPosition.x <= Game::mSCREEN_WIDTH + 101) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 105, rTransform.mPosition.y + 51, 106, 221);
	
	}
}



void TreeStump::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Oof! crashed right into a Tree Stump!\nWatch your path, Rex!");

	setSrcRect(0, 32, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 102, Game::mSCREEN_HEIGHT - 355, 273, 275);
}

void TreeStump::update() {
	TransformComponent& rTransform = getTransform();

	if (rTransform.mPosition.x <= Game::mSCREEN_WIDTH + 101) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 123, rTransform.mPosition.y + 162, 81, 110);
	
	}
}



void Stalker::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Hehe, the one-eyed Stalker...\nLook away next time, okay?");

	setAnimation(1, 2, 200);
	setSrcRect(32, 32, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 102, Game::mSCREEN_HEIGHT - 355, 273, 275);
}

void Stalker::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mPosition.x <= Game::mSCREEN_WIDTH + 101) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 115, rTransform.mPosition.y + 8, 123, 255);
	
	}

	rSrcRect.x = 32 + (rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount()));
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}



void Brute::init() {
	getCollider().resize(1);
	getCollider().setCollisionTag("Ouch, crushed by the merciless Brute!\nOh well, you're not THAT hurt, go again?");

	setAnimation(2, 2, 200);
	setSrcRect(0, 64, 32, 32);
	setTransform(Game::mSCREEN_WIDTH + 102, Game::mSCREEN_HEIGHT - 355, 273, 275);
}

void Brute::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mPosition.x <= Game::mSCREEN_WIDTH + 101) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 72, rTransform.mPosition.y + 59, 191, 213);
	
	}

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}


void StalkerPup::init() {
	auto upMidDown = std::rand() % 15;

	setAnimation(3, 2, 200);
	setSrcRect(0, 96, 32, 32);
	
	getCollider().resize(1);
	getCollider().setCollisionTag("Yikes, Stalker Pups...\nNothing to see or say here, Rex, run again?");

	if (upMidDown <= 5) {
		setTransform(Game::mSCREEN_WIDTH + 102, 150, 173, 175);
	}
	else if (upMidDown <= 10) {
		setTransform(Game::mSCREEN_WIDTH + 102, 280, 173, 175);
	}
	else {
		setTransform(Game::mSCREEN_WIDTH + 102, Game::mSCREEN_HEIGHT - 300, 173, 175);
	}
}

void StalkerPup::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mPosition.x <= Game::mSCREEN_WIDTH + 101) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 64, rTransform.mPosition.y, 109, 175);
	
	}

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}



void Gale::init() {
	auto upMidDown = std::rand() % 15;

	setAnimation(4, 2, 200);
	setSrcRect(0, 128, 32, 32);

	getCollider().resize(1);
	getCollider().setCollisionTag("Whoaa, you let the Night Gale sweep you away?\nHold on tight next run!");

	if (upMidDown <= 5) {
		setTransform(Game::mSCREEN_WIDTH + 102, 150, 173, 175);
	}
	else if (upMidDown <= 10) {
		setTransform(Game::mSCREEN_WIDTH + 102, 280, 173, 175);
	}
	else {
		setTransform(Game::mSCREEN_WIDTH + 102, Game::mSCREEN_HEIGHT - 300, 173, 175);
	}
}

void Gale::update() {
	TransformComponent& rTransform = getTransform();
	SDL_Rect& rSrcRect = getSrcRect();

	if (rTransform.mPosition.x <= Game::mSCREEN_WIDTH + 101) {

		getCollider().setColliderRect(0, rTransform.mPosition.x + 64, rTransform.mPosition.y, 109, 175);
	
	}

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}