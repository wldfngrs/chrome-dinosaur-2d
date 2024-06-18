#include "Text.h"
#include "Game.h"
#include "TextureManager.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

static void extractTextSegments(std::vector<std::string>& textSegments, std::vector<size_t>& textLineLen, std::string text) {
	size_t delimitingIndex;
	std::string delimitingText;
	if ((delimitingIndex = text.find("Dying Trees")) != std::string::npos) {
		delimitingText = "Dying Trees";
	}

	else if ((delimitingIndex = text.find("The Bucket")) != std::string::npos) {
		delimitingText = "The Bucket";
	}

	else if ((delimitingIndex = text.find("Tree Stump")) != std::string::npos) {
		delimitingText = "Tree Stump";
	}

	else if ((delimitingIndex = text.find("Stalker Pups")) != std::string::npos) {
		delimitingText = "Stalker Pups";
	}

	else if ((delimitingIndex = text.find("Stalker")) != std::string::npos) {
		delimitingText = "Stalker";
	}

	else if ((delimitingIndex = text.find("Brute")) != std::string::npos) {
		delimitingText = "Brute";
	}

	else if ((delimitingIndex = text.find("Night Gale")) != std::string::npos) {
		delimitingText = "Night Gale";
	}

	else {
		delimitingText = "";
		delimitingIndex = 0;
	}

	if (delimitingIndex != 0) {
		textSegments.push_back(std::string(text, 0, delimitingIndex));
		textSegments.push_back(delimitingText);
	}

	size_t start = delimitingIndex + delimitingText.size();
	size_t next = start;

	size_t lineindex = 0;

	for (; ;) {
		if ((next = text.find('\n', start)) == std::string::npos) {
			textSegments.push_back(std::string(text, start, text.size() - start));
			textLineLen.push_back(text.size() - (lineindex + 1));
			break;
		}
		else {
			textSegments.push_back(std::string(text, start, next - start));
			textSegments.push_back("\\n");
			textLineLen.push_back(next - lineindex);

			start = next + 1;
			lineindex = next;
		}
	}
}

TextManager::TextManager() {}

TextManager::~TextManager() {
	for (auto& t : mTextCache) {
		SDL_DestroyTexture(t.second);
	}

	mTextCache.clear();
}

static void setXpos(xPosition xpos, int& x, size_t lineLen, size_t letterWidth) {
	switch (xpos) {
	case CENTERED:
		x = static_cast<int>(Game::SCREEN_WIDTH / 2 - lineLen * letterWidth / 2);
		break;
	case RIGHT:
		x = static_cast<int>(Game::SCREEN_WIDTH - lineLen * letterWidth);
		break;
	case LEFT:
		x = 0;
	}
}

void TextManager::drawText_Static(std::string text, xPosition xpos, int y, size_t letterWidth, size_t letterHeight) {
	std::vector<std::string> textSegments;
	std::vector<size_t> lineLen;
	
	extractTextSegments(textSegments, lineLen, text);

	int lineLenIndex = 0;

	int x = 0;

	size_t w = textSegments[0].size() * letterWidth;
	size_t h = letterHeight;

	setXpos(xpos, x, lineLen[lineLenIndex++], letterWidth);

	TextureManager::drawText(mTextCache[textSegments[0]], x, y, w, h);

	for (size_t i = 1; i < textSegments.size(); i++) {
		if (textSegments[i] == "\\n") {
			y += static_cast<int>(h + 2);
			setXpos(xpos, x, lineLen[lineLenIndex++], letterWidth);
			w = textSegments[++i].size() * letterWidth;
			TextureManager::drawText(mTextCache[textSegments[i]], x, y, w, h);
		}
		else {
			x += static_cast<int>(w);
			w = textSegments[i].size() * letterWidth;
			TextureManager::drawText(mTextCache[textSegments[i]], x, y, w, h);
		}
	}
}

void TextManager::drawText_Static(std::string text, int x, int y, size_t letterWidth, size_t letterHeight) {
	std::vector<std::string> textSegments;
	std::vector<size_t> lineLen;

	extractTextSegments(textSegments, lineLen, text);

	int lineLenIndex = 0;

	size_t w = textSegments[0].size() * letterWidth;
	size_t h = letterHeight;

	TextureManager::drawText(mTextCache[textSegments[0]], x, y, w, h);

	for (size_t i = 1; i < textSegments.size(); i++) {
		if (textSegments[i] == "\\n") {
			y += static_cast<int>(h + 2);
			w = textSegments[++i].size() * letterWidth;
			TextureManager::drawText(mTextCache[textSegments[i]], x, y, w, h);
		}
		else {
			x += static_cast<int>(w);
			w = textSegments[i].size() * letterWidth;
			TextureManager::drawText(mTextCache[textSegments[i]], x, y, w, h);
		}
	}
}

void TextManager::drawText_NonStatic(std::string text, int x, int y, size_t letterWidth, size_t letterHeight) {
	size_t spaces = 7 - text.size();

	for (size_t i = 0; i < spaces; i++) {
		TextureManager::drawText(mTextCache[" "], x, y, letterWidth, letterHeight);
		x += static_cast<int>(letterWidth + 1);
	}

	for (size_t i = 0; i < text.size(); i++) {
		std::string txt;
		txt += text[i];

		TextureManager::drawText(mTextCache[txt], x, y, letterWidth, letterHeight);
		
		x += static_cast<int>(letterWidth + 1);
	}
}

void TextManager::drawText_NonStatic(std::string text, xPosition xpos, int y, size_t letterWidth, size_t letterHeight) {
	size_t spaces = 7 - text.size();

	int x = 0;

	setXpos(xpos, x, text.size(), letterWidth);

	for (size_t i = 0; i < spaces; i++) {
		TextureManager::drawText(mTextCache[" "], x, y, letterWidth, letterHeight);
		x += static_cast<int>(letterWidth + 1);
	}

	for (size_t i = 0; i < text.size(); i++) {
		std::string txt;
		txt += text[i];

		TextureManager::drawText(mTextCache[txt], x, y, letterWidth, letterHeight);

		x += static_cast<int>(letterWidth + 1);
	}
}

void TextManager::drawText_Static_NonStatic(std::string text1, std::string text2, xPosition xpos, int y, size_t letterWidth, size_t letterHeight) {
	size_t textlen = text1.size() + text2.size();

	int x = 0;
	setXpos(xpos, x, textlen, letterWidth);
	size_t w = text1.size() * letterWidth;
	TextureManager::drawText(mTextCache[text1], x, y, w, letterHeight);

	x += static_cast<int>(w + 1);

	w = text2.size() * letterWidth;
	for (size_t i = 0; i < text2.size(); i++) {
		std::string txt;
		txt += text2[i];

		TextureManager::drawText(mTextCache[txt], x, y, letterWidth, letterHeight);

		x += static_cast<int>(letterWidth + 1);
	}
}

void TextManager::addToTextCache_Static(std::string text, const char* fontPath, const int fontIndex, SDL_Color color) {
	TTF_Font* font = TTF_OpenFont(fontPath, fontIndex);

	if (font == nullptr) {
		std::stringstream ss;
		ss << "[Error] TextManager::init(): '" << fontPath << "' TTF_OpenFont() failed!\nDetails: " << TTF_GetError();
		Game::errorMessage = ss.str();
		mErrorCode = -1;

		return;
	}

	mTextCache[text] = TextureManager::loadTextTexture(text, font, color);

	TTF_CloseFont(font);
}

void TextManager::addToTextCache_NonStatic(std::string text, const char* fontPath, const int fontIndex, SDL_Color color) {
	TTF_Font* font = TTF_OpenFont(fontPath, fontIndex);
	
	if (font == nullptr) {
		std::stringstream ss;
		ss << "[Error] TextManager::init(): '" << fontPath << "' TTF_OpenFont() failed!\nDetails: " << TTF_GetError();
		Game::errorMessage = ss.str();
		mErrorCode = -1;

		return;
	}

	for (size_t i = 0; i < text.size(); i++) {
		std::string txt;
		txt += text[i];
		mTextCache[txt] = TextureManager::loadTextTexture(txt, font, color);
	}

	TTF_CloseFont(font);
}

void TextManager::init() {
	SDL_Color dinoRed = { 184, 37, 53 };
	SDL_Color snowWhite = { 255, 255, 255 };

	addToTextCache_Static("DINO SAUR", "assets\\fonts\\Marshland_Beauty.otf", 72, dinoRed);
	addToTextCache_Static("press [SPACE] to start", "assets\\fonts\\ALBA____.TTF", 36, snowWhite);
	addToTextCache_Static("press [SPACE] to run again!", "assets\\fonts\\ALBA____.TTF", 36, snowWhite);

	addToTextCache_Static("HIGH SCORE: ", "assets\\fonts\\junegull.ttf", 48, snowWhite);
	addToTextCache_Static("CURRENT SCORE: ", "assets\\fonts\\junegull.ttf", 48, snowWhite);
	addToTextCache_NonStatic("0123456789", "assets\\fonts\\junegull.ttf", 48, snowWhite);
	addToTextCache_NonStatic(" ", "assets\\fonts\\junegull.ttf", 48, snowWhite);

	addToTextCache_Static("Sh*t! caught in the ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("Dying Trees", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_Static("!", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("Wriggle out for your next run?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
  
	addToTextCache_Static("Danmit! You've kicked ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("The Bucket", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_Static("Did I mention you have nine (ahem) lives?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);

	addToTextCache_Static("Oof! crashed right into a ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("Tree Stump", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_Static("Watch your path, Rex!", "assets\\fonts\\adrip1.ttf", 72, snowWhite);

	addToTextCache_Static("Hehe, the one-eyed ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("Stalker", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_Static("...", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("Look away next time, okay?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);

	addToTextCache_Static("Yikes, ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("Stalker Pups", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_Static("Nothing to see or say here, Rex, run again?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);

	addToTextCache_Static("Ouch, crushed by the merciless ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("Brute", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_Static("Oh well, you're not THAT hurt, go again?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);


	addToTextCache_Static("Whoaa, you let the ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("Night Gale", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_Static(" sweep you away?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_Static("Hold on tight next run!", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
}

int TextManager::getErrorCode() const {
	return mErrorCode;
}