#include "Score.h"
#include "Game.h"

int Score::mHighscore;
int Score::mCurrentscore;


void Score::init() {
	mCurrentscore = 1;
	mHighscore = 0;
}

void Score::reset() {
	mCurrentscore = 1;
}

void Score::update() {
	static int toggleSignal = 1000;
	if (Game::mTick % 7 == 0) mCurrentscore++;

	if (mCurrentscore == 100) {
		Game::mGameCompleted = true;
		return;
	}

	if (mCurrentscore % toggleSignal == 0) {
		Game::mSpeedToggled = Game::mSpeedToggled ? false : true;

		toggleSignal = ((toggleSignal == 1000) ? 50 : 1000);
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

int& Score::getHighScore() {
	return mHighscore;
}
int& Score::getCurrentScore() {
	return mCurrentscore;
}