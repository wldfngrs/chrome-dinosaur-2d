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
	if (Game::tick % 7 == 0) mCurrentscore++;
}

void Score::draw() {
	int digitsXPosition = Game::SCREEN_WIDTH - 8 * 18;
	int highScoreXPosition = Game::SCREEN_WIDTH - (12 * 18 + 8 * 18);
	int currentScoreXPosition = highScoreXPosition - 55;


	Game::textManager.drawText_Static("HIGH SCORE: ", highScoreXPosition, 10, 18, 40);
	Game::textManager.drawText_NonStatic(std::to_string(mHighscore), digitsXPosition, 10, 18, 40);
	Game::textManager.drawText_Static("CURRENT SCORE: ", currentScoreXPosition, 60, 18, 40);
	Game::textManager.drawText_NonStatic(std::to_string(mCurrentscore), digitsXPosition, 60, 18, 40);
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