#include "Sprites.h"
#include "Score.h"

void Background::init() {
	setAnimation(1, 2, 500);
}

void Background::update() {
	static int animationIndex = 1;
	static int switchCount = 700;
	
	if (Score::getCurrentScore() % switchCount == 0) {
		switch (animationIndex) {
		case 0:
			setAnimation(1, 2, 500);
			animationIndex = 1;
			switchCount = 700;
			break;
		case 1:
			setAnimation(0, 2, 500);
			animationIndex = 0;
			switchCount = 140;
			break;
		}
	}
	
	SDL_Rect& rSrcRect = getSrcRect();

	rSrcRect.x = rSrcRect.w * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
	rSrcRect.y = getSheetIndex() * rSrcRect.h;
}

void CelestialBody::update() {
	TransformComponent& rTransform = getTransform();

	rTransform.mVelocity.x = -3;

	if (rTransform.mPosition.x <= -rTransform.mWidth) {
		rTransform.mPosition.x = Game::mSCREEN_WIDTH;
	}
}

//void Ground::init() {
//	setAnimation(0, 3, 200);
//}

//void Ground::update() {
//	SDL_Rect& rSrcRect = getSrcRect();
//
//	rSrcRect.y = rSrcRect.h * static_cast<int>((SDL_GetTicks() / getFramesSpeed()) % getFramesCount());
//	rSrcRect.x = getSheetIndex() * rSrcRect.w;
//}