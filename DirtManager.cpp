#include "DirtManager.h"
#include "TextureManager.h"
#include "Game.h"

#include <random>

bool DirtManager::isPositionOccupied(int x, int y) {
	for (const auto& dirt : mDirt) {
		if (x + dirt.mWidth >= dirt.x
			&&
			dirt.x + dirt.mWidth >= x
			&&
			y + dirt.mHeight >= dirt.y
			&&
			dirt.y + dirt.mHeight >= y)
		{
			return true;
		}
	}

	return false;
}

void DirtManager::setTexture() {
	mTexture = TextureManager::loadSpriteTexture("assets\\sprites\\GroundSheet.png");
}

void DirtManager::setRect(SDL_Rect& rect, int x, int y, int w, int h) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void DirtManager::init() {
	setTexture();
	setRect(mSrcRectGround, 0, 0, 96, 16);
	setRect(mSrcRectDirt, 0, 16, 16, 16);

	setRect(mDestRectGround, 0, Game::mSCREEN_HEIGHT - 80, Game::mSCREEN_WIDTH, 80);

	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> yDistr(Game::mSCREEN_HEIGHT - 80, Game::mSCREEN_HEIGHT - 45);
	std::uniform_int_distribution<> xDistr(0, Game::mSCREEN_WIDTH);

	for (int i = 0; i < (Game::mSCREEN_WIDTH / Game::mSCREEN_WIDTH) * 70; i++) {
		int x = xDistr(gen);
		int y = yDistr(gen);

		int len = generateDirtLen(x);

		if (isPositionOccupied(x, y)) {
			i--;
		}
		else {
			mDirt.emplace_back(x, y, len, 5);
		}
	}
}

void DirtManager::update() {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> yDistr(Game::mSCREEN_HEIGHT - 80, Game::mSCREEN_HEIGHT);

	for (auto& dirt : mDirt) {
		dirt.x += mDirtVelocity;
	
		if (dirt.x < -dirt.mWidth) {
			dirt.x = Game::mSCREEN_WIDTH;
			dirt.y = yDistr(gen);
		}
	}
}

void DirtManager::draw() {
	TextureManager::drawSprite(mTexture, mSrcRectGround, mDestRectGround);

	for (auto& dirt : mDirt) {
		setRect(mDestRectDirt, dirt.x, dirt.y, dirt.mWidth, dirt.mHeight);

		TextureManager::drawSprite(mTexture, mSrcRectDirt, mDestRectDirt);
	}
}

int DirtManager::generateDirtLen(int seed) {
	int len(0);
	if (seed <= 400) {
		len = 20;
	}
	else if (seed <= 800) {
		len = 25;
	}
	else {
		len = 30;
	}

	return len;
}