#pragma once

#include "SDL.h"

#include <map>
#include <string>
#include <vector>

//
// Basically, newlines and Obstacle names (as strings) are segment delimiters.
//
//

enum position {
	CENTERED,
	NOTCENTERED,
};

class TextManager {
	std::map<std::string, SDL_Texture*> textCache;

	void extractTextSegments(std::vector<std::string>& segments, std::vector<int>& lineLen, std::string text);

	void drawTextSegments(std::vector<std::string> segments, std::vector<int> lineLen, int x, int y, int letterWidth, int letterHeight);

	void addToTextCache(std::string text, const char* fontPath, const int fontIndex, SDL_Color color, bool isStatic);

public:
	int errorCode = 0;
	std::string errorMessage;

	TextManager();

	~TextManager();

	void init();
	void update();
	void drawText(std::string t, int x, int y, int letterWidth, int letterHeight, bool isStatic);
};