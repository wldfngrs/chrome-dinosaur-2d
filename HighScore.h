#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Font.h"

#include <memory>

class HighScore {
public:
	static int score;
	static std::unique_ptr<Font> scoreFont;
};