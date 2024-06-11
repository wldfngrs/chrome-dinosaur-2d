#pragma once

#include "SDL.h"

#include <map>
#include <string>

enum TEXTPOSITION {
	LEFT	= 1 << 0,
	RIGHT	= 1 << 1,
	DOWN	= 1 << 2,
	UP		= 1 << 3,
	CENTER	= 1 << 4
};

class TextManager {
	static std::map<std::string, SDL_Texture*> textCache;

	void addToTextCache(std::string text, const char* fontPath, const int fontIndex, SDL_Color color, bool isStatic);

	void draw(std::string text, int x, int y, int w, int h, bool isStatic);

public:
	int errorCode = 0;
	std::string errorMessage;

	TextManager();

	~TextManager();

	void init();

	void update();
	
	void drawAtSpecifiedPosition(std::string text, int x, int y, int w, int h, bool isStatic);

	void drawAtStandardPosition(std::string text, int position, int w, int h, bool isStatic);
};