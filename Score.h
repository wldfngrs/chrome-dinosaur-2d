#pragma once

class Score {
	static int mHighscore;
	static int mCurrentscore;
public:
	Score() = delete;

	static void init();
	static void reset();
	static void update();
	static void draw();

	static int& getHighScore();
	static int& getCurrentScore();

	static void setHighScore(int highscore);
};