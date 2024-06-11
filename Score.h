#pragma once

class Score {
public:
	static int highscore;
	static int currentscore;

	static void init();
	static void reset();
	static void update();
};