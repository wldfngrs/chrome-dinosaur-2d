#include "Score.h"
#include "Game.h"

int Score::mHighscore;
int Score::mCurrentscore;
int Score::mToggleTick = 0;
int Score::mToggleSignal = 1000;

void Score::init() {
	mCurrentscore = 1;
	mHighscore = 0;
}

void Score::reset() {
	mCurrentscore = 1;
	mToggleTick = 0;
}

void Score::update() {
	if (Game::mTick % 7 == 0) {
		mCurrentscore++;
		mToggleTick++;
	}

	if (mCurrentscore >= 10000) {
		mCurrentscore == 10000;
		Game::mGameCompleted = true;
		return;
	}

	if (mToggleTick >= mToggleSignal) {
		mToggleTick = 0;

		Game::mSpeedToggled = Game::mSpeedToggled ? false : true;
	
		mToggleSignal = Game::mSpeedToggled ? 300 : 1000;
	}
}

void Score::draw(Game& game) {
	int digitsXPosition = Game::mSCREEN_WIDTH - 8 * 18;
	int highScoreXPosition = Game::mSCREEN_WIDTH - (12 * 18 + 8 * 18);
	int currentScoreXPosition = highScoreXPosition - 55;

	TextManager& rTextManager = game.getTextManager();

	rTextManager.drawText_Static("HIGH SCORE: ", highScoreXPosition, 10, 18, 40, INSTANT);
	rTextManager.drawText_NonStatic(std::to_string(mHighscore), digitsXPosition, 10, 18, 40);
	rTextManager.drawText_Static("CURRENT SCORE: ", currentScoreXPosition, 60, 18, 40, INSTANT);
	rTextManager.drawText_NonStatic(std::to_string(mCurrentscore), digitsXPosition, 60, 18, 40);
}

void Score::setHighScore(int highscore) {
	mHighscore = highscore;
}

int Score::getHighScore() {
	return mHighscore;
}
int Score::getCurrentScore() {
	return mCurrentscore;
}