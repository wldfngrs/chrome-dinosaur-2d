#include "Game.h"
#include "Sprites.h"
#include "KeyboardController.h"
#include "DinoStates.h"

Dino::~Dino() {
	clearState();
}

void Dino::init() {
	clearState();
	setState(new RunningState());
	mState->enter(*this);
}

void Dino::update() {
	mState->update(*this);
}

void Dino::press_UP_key() {
	if (!mJumping) {
		mState->leave(*this);
		clearState();
		setState(new JumpingState());
		mState->enter(*this);
	}
}

void Dino::press_DOWN_key() {
	if (!mDucking) {
		mState->leave(*this);
		clearState();
		setState(new DuckingState());
		mState->enter(*this);
	}
}

void Dino::release_DOWN_key() {
	if (!mRunning) {
		mState->leave(*this);
		clearState();
		setState(new RunningState());
		mState->enter(*this);
	}
}

DinoState* Dino::getState() const {
	return mState;
}
void Dino::setState(DinoState* state) {
	mState = state;
}

void Dino::clearState() {
	if (mState != nullptr) {
		delete mState;
	}
}

void Dino::startDuck() {
	mDucking = true;
	mJumping = false;
	mRunning = false;
}
void Dino::stopDuck() {
	mDucking = false;
}

void Dino::startJump() {
	mJumping = true;
	mDucking = false;
	mRunning = false;

	#ifdef __EMSCRIPTEN__
		int id = SND_DINO_JUMP
		emscripten_async_call(playSoundWrapper, &id, 0);
	#else
		Game::mSoundManager.playSound(SND_DINO_JUMP, CH_DINO);
	#endif
}
void Dino::stopJump() {
	mJumping = false;

	#ifdef __EMSCRIPTEN__
		int id = SND_DINO_LAND
		emscripten_async_call(playSoundWrapper, &id, 0);
	#else
		Game::mSoundManager.playSound(SND_DINO_LAND, CH_DINO);
	#endif
}

void Dino::startRun() {
	mRunning = true;
	mDucking = false;
	mJumping = false;
}
void Dino::stopRun() {
	mRunning = false;
}