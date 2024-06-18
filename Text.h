#pragma once

#include "SDL.h"

#include <map>
#include <string>

enum xPosition {
	CENTERED,
	LEFT,
	RIGHT,
};

class TextManager {
	std::map<std::string, SDL_Texture*> mTextCache;

	void addToTextCache_NonStatic(std::string text, const char* fontPath, const int fontIndex, SDL_Color color);
	void addToTextCache_Static(std::string text, const char* fontPath, const int fontIndex, SDL_Color color);

public:

	TextManager();

	~TextManager();

	void init();

	void drawText_Static_NonStatic(std::string text1, std::string text2, xPosition xpos, int y, size_t letterWidth, size_t letterHeight);
	void drawText_Static(std::string text, xPosition xpos, int y, size_t letterWidth, size_t letterHeight);
	void drawText_Static(std::string text, int x, int y, size_t letterWidth, size_t letterHeight);
	void drawText_NonStatic(std::string text, xPosition x, int y, size_t letterWidth, size_t letterHeight);
	void drawText_NonStatic(std::string text, int x, int y, size_t letterWidth, size_t letterHeight);
};