#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Font.h"

#include <memory>

class Score {
public:
	static int highscore;
	static int currentscore;
	static std::unique_ptr<Font> font;

	static void init();
	static void reset();
	static void update();
};