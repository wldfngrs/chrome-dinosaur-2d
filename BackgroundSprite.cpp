#include "Sprites.h"
#include "Game.h"
#include "Score.h"

void Background::init() {
	setAnimation(1, 2, 200);
}

void Background::update() {
	static int animationIndex = 1;
	static int switchCount = 350;
	
	if (Score::getCurrentScore() % switchCount == 0) {
		switch (animationIndex) {
		case 0:
			if (Game::mSpeedToggled) {
				setAnimation(0, 2, 150);
			}
			else {
				setAnimation(0, 2, 200);
			}

			Game::mSoundManager.playMusic(NIGHT_MUSIC);

			animationIndex = 1;
			switchCount = 800;
			break;
		case 1:
			setAnimation(1, 2, 200);

			if (Game::mSpeedToggled) {
				setAnimation(1, 2, 150);
			}
			else {
				setAnimation(1, 2, 200);
			}

			if (Game::mSoundManager.getCurrentPlayingMusic() == NIGHT_MUSIC) {
				Game::mSoundManager.playMusic(MORNING_MUSIC);
				animationIndex = 1;
				switchCount = 350;
			}
			else if (Game::mSoundManager.getCurrentPlayingMusic() == MORNING_MUSIC) {
				Game::mSoundManager.playMusic(NOON_MUSIC);
				animationIndex = 0;
				switchCount = 700;
			}

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
		rTransform.mVelocity.x = Game::mSpeedToggled ? -15 : -3;
	}
}