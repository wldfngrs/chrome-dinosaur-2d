#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

#include <iostream>

class Font {
public:
	const char* pathToFont;
	int indexToFont;
	int errorCode = 0;
	SDL_Texture* texture;
	TTF_Font* font;

	Font(const char* fontPath, const int fontIndex) {
		fontPath = const_cast<char*>(fontPath);
		indexToFont = fontIndex;
		font = TTF_OpenFont(fontPath, indexToFont);

		if (font == nullptr) {
			errorCode = -1;
		}
	}

	~Font() {
		SDL_DestroyTexture(texture);
		TTF_CloseFont(font);
	}
};
