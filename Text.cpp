#include "Text.h"
#include "Game.h"
#include "TextureManager.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>

std::map<std::string, SDL_Texture*> TextManager::textCache;

TextManager::TextManager() {}

TextManager::~TextManager() {
	for (auto& t : textCache) {
		SDL_DestroyTexture(t.second);
	}

	textCache.clear();
}

void TextManager::addToTextCache(std::string text, const char* fontPath, const int fontIndex, SDL_Color color, bool isStatic) {
	TTF_Font* font = TTF_OpenFont(fontPath, fontIndex);

	if (font == nullptr) {
		std::stringstream ss;
		ss << "[Error] TextManager::init(): '" << fontPath << "' TTF_OpenFont() failed!\nDetails: " << TTF_GetError();
		errorMessage = ss.str();
		errorCode = -1;
	}

	if (isStatic) {
		textCache[text] = TextureManager::loadTextTexture(text, font, color);
	}
	else {
		for (auto t : text) {
			std::string txt;
			txt += t;
			textCache[txt] = TextureManager::loadTextTexture(txt, font, color);
		}
	}

	TTF_CloseFont(font);
}

void TextManager::draw(std::string text, int x, int y, int w, int h, bool isStatic) {
	if (isStatic) {
		TextureManager::drawText(textCache[text], x, y, w, h);
	}
	else {
		//int texW = 0, texH = 0;
		//TextureManager::getTextureWidthHeight(textCache[" "], &texW, &texH);

		auto numSpaces = 8 - text.size();
		int letterSize = w / 8;
		int spacing = 1;
		for (auto i = 0; i < numSpaces; i++) {
			TextureManager::drawText(textCache[" "], x, y, w, h);
			x = x + letterSize + spacing;
		}

		for (auto t : text) {
			std::string txt;
			txt += text[0];
			TextureManager::drawText(textCache[txt], x, y, w, h);
			x = x + letterSize + spacing;
		}
	}
}

void TextManager::init() {
	SDL_Color dinoRed = { 184, 37, 53 };
	SDL_Color snowWhite = { 255, 255, 255 };
	addToTextCache("DINO SAUR", "assets\\fonts\\Marshland_Beauty.otf", 72, dinoRed, true);
	addToTextCache("press [SPACE] to start", "assets\\fonts\\ALBA____.TTF", 12, snowWhite, true);

	addToTextCache("HIGH SCORE", "assets\\fonts\\ALBA____.TTF", 12, snowWhite, true);
	addToTextCache("CURRENT SCORE", "assets\\fonts\\ALBA____.TTF", 12, snowWhite, true);
	addToTextCache("0123456789", "assets\\fonts\\ALBA____.TTF", 12, snowWhite, false);
	addToTextCache(" ", "assets\\fonts\\ALBA____.TTF", 12, snowWhite, true);

	addToTextCache("Sh*t! caught in the Dying Trees!\nWriggle out for your next run?", "assets\\fonts\\adrip1.ttf", 48, snowWhite, true);
	addToTextCache("Danmit! You've kicked the Bucket.\nDid I mention you have nine (ahem) lives?", "assets\\fonts\\adrip1.ttf", 48, snowWhite, true);
	addToTextCache("Oof! crashed right into a Tree Stump!\nWatch your path, Rex.", "assets\\fonts\\adrip1.ttf", 48, snowWhite, true);
	addToTextCache("Hehe, the one-eyed Stalker...\nLook away next time, okay?", "assets\\fonts\\adrip1.ttf", 48, snowWhite, true);
	addToTextCache("Yikes, Stalker Pups...\nNothing to say here, run again?", "assets\\fonts\\adrip1.ttf", 48, snowWhite, true);
	addToTextCache("Ouch, crushed by the merciless Brute!\nOh well, you're not THAT hurt, go again?", "assets\\fonts\\adrip1.ttf", 48, snowWhite, true);
	addToTextCache("Whoaa, you let the Night Gale sweep you away?\nHold on tight next run!", "assets\\fonts\\adrip1.ttf", 48, snowWhite, true);
}

void TextManager::update() {}

void TextManager::drawAtSpecifiedPosition(std::string text, int x, int y, int w, int h, bool isStatic) {
	draw(text, x, y, w, h, isStatic);
}

void TextManager::drawAtStandardPosition(std::string text, int position, int w, int h, bool isStatic) {
	int x, y;

	if (((position & LEFT) && (position & RIGHT)) || ((position & UP) && (position & DOWN)) || ((position & LEFT) && (position & UP))) {
		x = 0;
		y = 0;
	}

	if ((position & CENTER)) {
		x = Game::SCREEN_WIDTH / 2;
		y = Game::SCREEN_HEIGHT / 2;
	}

	if ((position & LEFT) && (position & CENTER)) {
		x = 0;
		y = Game::SCREEN_HEIGHT / 2;
	}

	if ((position & LEFT) && (position & DOWN)) {
		x = 0;
		y = Game::SCREEN_HEIGHT;
	}

	if ((position & UP) && (position & CENTER)) {
		x = Game::SCREEN_WIDTH / 2;
		y = 0;
	}

	if ((position & DOWN) && (position & CENTER)) {
		x = Game::SCREEN_WIDTH / 2;
		y = Game::SCREEN_HEIGHT;
	}

	if ((position & RIGHT) && (position & UP)) {
		x = Game::SCREEN_WIDTH;
		y = 0;
	}

	if ((position & RIGHT) && (position & CENTER)) {
		x = Game::SCREEN_WIDTH;
		y = Game::SCREEN_HEIGHT / 2;
	}

	if ((position & RIGHT) && (position & DOWN)) {
		x = Game::SCREEN_WIDTH;
		y = Game::SCREEN_HEIGHT;
	}

	draw(text, x, y, w, h, isStatic);
}