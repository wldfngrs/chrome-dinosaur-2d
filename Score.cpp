#include "Score.h"
#include "Game.h"

int Score::highscore;
int Score::currentscore;


void Score::init() {
	currentscore = 0;
	highscore = 0;
}

void Score::reset() {
	currentscore = 0;
}

void Score::update() {
	if (Game::tick % 7) currentscore++;

	if (currentscore > highscore) {
		highscore = currentscore;
	}
}