#include "Text.h"
#include "Game.h"
#include "TextureManager.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <map>

static std::vector<std::string> extractTextSegments(std::string text) {
	size_t delimitingIndex;
	std::string delimitingText;

	std::vector<std::string> textSegments;

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

	for (; ;) {
		if ((next = text.find('\n', start)) == std::string::npos) {
			textSegments.push_back(std::string(text, start, text.size() - start));
			break;
		}
		else {
			textSegments.push_back(std::string(text, start, next - start));
			textSegments.push_back("\\n");

			start = next + 1;
		}
	}

	return textSegments;
}

TextManager::~TextManager() {
	for (auto& text : mTextCache) {
		SDL_DestroyTexture(text.second);
	}

	mTextCache.clear();
}

static int calculateXPosition(std::vector<std::string> textSegments, size_t indexIntoTextSegments, xPosition xpos, size_t letterWidth, renderEffect effect) {
	int x = 0;
	int textWidth = 0;
	int index = indexIntoTextSegments;
	
	if (effect == TYPEWRITER) {
		for (size_t i = 0; i < textSegments[index].size(); i++) {
			std::string letter;
			letter += textSegments[index][i];

			if (letter == "i" || letter == "!" || letter == "," || letter == "." || letter == "l" || letter == "I" || letter == "'") {
				textWidth += letterWidth / 2;
			}
			else {
				textWidth += letterWidth;
			}
		}
	}
	else {
		for (size_t i = index; i < textSegments.size(); i++) {
			if (textSegments[i] == "\\n") {
				break;
			}

			textWidth += textSegments[i].size() * letterWidth;
		}
	}


	switch (xpos) {
	case CENTERED:
		x = static_cast<int>(Game::mSCREEN_WIDTH / 2 - textWidth / 2);
		break;
	case RIGHT:
		x = static_cast<int>(Game::mSCREEN_WIDTH - textWidth);
		break;
	case LEFT:
		x = 0;
	}

	return x;
}

void TextManager::typeWriterDrawAndRender(std::string lineOfText, int x, int y, size_t letterWidth, size_t letterHeight) {
	for (size_t i = 0; i < lineOfText.size(); i++) {
		std::string letter;
		letter += lineOfText[i];

		if (letter == "i" || letter == "!" || letter == "," || letter == "." || letter == "l" || letter == "I" || letter == "'") {
			TextureManager::drawText(mTextCache[letter], x, y, letterWidth / 2, letterHeight);
			x += static_cast<int>((letterWidth / 2) + 1);
		}
		else {
			TextureManager::drawText(mTextCache[letter], x, y, letterWidth, letterHeight);
			x += static_cast<int>(letterWidth + 1);
		}

		SDL_RenderPresent(Game::mGameRenderer);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void TextManager::drawText_Static(std::string text, xPosition xpos, int y, size_t letterWidth, size_t letterHeight, renderEffect effect) {
	std::vector<std::string> textSegments = extractTextSegments(text);

	int x = calculateXPosition(textSegments, 0, xpos, letterWidth, effect);

	if (effect == TYPEWRITER) {
		typeWriterDrawAndRender(textSegments[0], x, y, letterWidth, letterHeight);
	}
	else {
		
		TextureManager::drawText(mTextCache[textSegments[0]], x, y, textSegments[0].size() * letterWidth, letterHeight);
	}

	for (size_t i = 1; i < textSegments.size(); i++) {
		if (textSegments[i] == "\\n") {
			y += static_cast<int>(letterHeight + 2);
			x = calculateXPosition(textSegments, ++i, xpos, letterWidth, effect);
		}
		else {
			x += static_cast<int>(textSegments[i - 1].size() * letterWidth);
		}

		
		if (effect == TYPEWRITER) {
			typeWriterDrawAndRender(textSegments[i], x, y, letterWidth, letterHeight);
		}
		else {
			TextureManager::drawText(mTextCache[textSegments[i]], x, y, textSegments[i].size() * letterWidth, letterHeight);
		}
	}
}

void TextManager::drawText_Static(std::string text, int x, int y, size_t letterWidth, size_t letterHeight, renderEffect effect) {
	std::vector<std::string> textSegments = extractTextSegments(text);

	size_t textWidth = textSegments[0].size() * letterWidth;

	if (effect == TYPEWRITER) {
		typeWriterDrawAndRender(textSegments[0], x, y, letterWidth, letterHeight);
	}
	else {
		TextureManager::drawText(mTextCache[textSegments[0]], x, y, textWidth, letterHeight);
	}

	for (size_t i = 1; i < textSegments.size(); i++) {
		if (textSegments[i] == "\\n") {
			y += static_cast<int>(letterHeight + 2);
			textWidth = textSegments[++i].size() * letterWidth;
		}
		else {
			x += static_cast<int>(textWidth);
			textWidth = textSegments[i].size() * letterWidth;
		}

		if (effect == TYPEWRITER) {
			typeWriterDrawAndRender(textSegments[i], x, y, letterWidth, letterHeight);
		}
		else {
			TextureManager::drawText(mTextCache[textSegments[i]], x, y, textWidth, letterHeight);
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
		std::string num;
		num += text[i];

		TextureManager::drawText(mTextCache[num], x, y, letterWidth, letterHeight);

		x += static_cast<int>(letterWidth + 1);
	}
}

void TextManager::drawText_NonStatic(std::string text, xPosition xpos, int y, size_t letterWidth, size_t letterHeight) {
	int spaces = 7 - text.size();

	std::vector<std::string> textSegments = extractTextSegments(text);

	int x = calculateXPosition(textSegments, 0, xpos, letterWidth, INSTANT);

	for (int i = 0; i < spaces; i++) {
		TextureManager::drawText(mTextCache[" "], x, y, letterWidth, letterHeight);
		x += static_cast<int>(letterWidth + 1);
	}

	for (size_t i = 0; i < text.size(); i++) {
		std::string num;
		num += text[i];

		TextureManager::drawText(mTextCache[num], x, y, letterWidth, letterHeight);

		x += static_cast<int>(letterWidth + 1);
	}
}

void TextManager::drawText_Static_NonStatic(std::string text1, std::string text2, xPosition xpos, int y, size_t letterWidth, size_t letterHeight) {
	std::vector<std::string> textSegments = extractTextSegments(text1 + text2);

	int x = calculateXPosition(textSegments, 0, xpos, letterWidth, INSTANT);

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

void TextManager::addToTextCache_AllAtOnce(std::string text, const char* fontPath, const int fontIndex, SDL_Color color) {
	TTF_Font* font = TTF_OpenFont(fontPath, fontIndex);

	if (font == nullptr) {
		std::cerr << "[Error] TextManager::init(): '" << fontPath << "' TTF_OpenFont() failed!\nDetails: " << TTF_GetError() << "\n\n";
		return;
	}

	mTextCache[text] = TextureManager::loadTextTexture(text, font, color);

	TTF_CloseFont(font);
}

void TextManager::addToTextCache_CharByChar(std::string text, const char* fontPath, const int fontIndex, SDL_Color color) {
	TTF_Font* font = TTF_OpenFont(fontPath, fontIndex);

	if (font == nullptr) {
		std::cerr << "[Error] TextManager::init(): '" << fontPath << "' TTF_OpenFont() failed!\nDetails: " << TTF_GetError() << "\n\n";
		return;
	}

	for (size_t i = 0; i < text.size(); i++) {
		std::string txt;
		txt += text[i];

		if (mTextCache.find(txt) == mTextCache.end()) {
			mTextCache[txt] = TextureManager::loadTextTexture(txt, font, color);
		}
	}

	TTF_CloseFont(font);
}

void TextManager::init() {
	SDL_Color dinoRed = { 184, 37, 53 };
	SDL_Color snowWhite = { 255, 255, 255 };

	addToTextCache_AllAtOnce("DINO SAUR", "assets\\fonts\\Marshland_Beauty.otf", 72, dinoRed);
	addToTextCache_AllAtOnce("press [SPACE] to start", "assets\\fonts\\ALBA____.TTF", 36, snowWhite);
	addToTextCache_AllAtOnce("a 2D remake of the classic Chrome dinosaur game", "assets\\fonts\\ALBA____.TTF", 36, snowWhite);
	addToTextCache_AllAtOnce("by wldfngrs; https://github.com/wldfngrs", "assets\\fonts\\ALBA____.TTF", 36, snowWhite);
	addToTextCache_AllAtOnce("press [SPACE] to run again, [ALT + F4] to quit...", "assets\\fonts\\ALBA____.TTF", 36, snowWhite);

	addToTextCache_AllAtOnce("HIGH SCORE: ", "assets\\fonts\\junegull.ttf", 48, snowWhite);
	addToTextCache_AllAtOnce("CURRENT SCORE: ", "assets\\fonts\\junegull.ttf", 48, snowWhite);
	addToTextCache_CharByChar("0123456789", "assets\\fonts\\junegull.ttf", 48, snowWhite);
	addToTextCache_CharByChar(" ", "assets\\fonts\\junegull.ttf", 48, snowWhite);

	addToTextCache_CharByChar("Congratulations! You beat the game!", "assets\\fonts\\ALBA____.TTF", 48, snowWhite);
	addToTextCache_CharByChar("It's no big deal, and certainly no difficult task, yet...", "assets\\fonts\\ALBA____.TTF", 48, snowWhite);
	addToTextCache_CharByChar("I appreciate you for playing this long!", "assets\\fonts\\ALBA____.TTF", 48, snowWhite);
	addToTextCache_CharByChar("I had fun working on this. I hope you had fun playing as well!", "assets\\fonts\\ALBA____.TTF", 48, snowWhite);
	addToTextCache_CharByChar("Have a great day, anon!", "assets\\fonts\\ALBA____.TTF", 48, snowWhite);

	addToTextCache_AllAtOnce("Sh*t! caught in the ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("Dying Trees", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_AllAtOnce("!", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("Wriggle out for your next run?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);

	addToTextCache_AllAtOnce("Danmit! You've kicked ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("The Bucket", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_AllAtOnce("Did I mention you have nine (ahem) lives?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);

	addToTextCache_AllAtOnce("Oof! crashed right into a ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("Tree Stump", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_AllAtOnce("Watch your path, Rex!", "assets\\fonts\\adrip1.ttf", 72, snowWhite);

	addToTextCache_AllAtOnce("Hehe, the one-eyed ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("Stalker", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_AllAtOnce("...", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("Look away next time, okay?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);

	addToTextCache_AllAtOnce("Yikes, ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("Stalker Pups", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_AllAtOnce("Nothing to see or say here, Rex, run again?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);

	addToTextCache_AllAtOnce("Ouch, crushed by the merciless ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("Brute", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_AllAtOnce("Oh well, you're not THAT hurt, go again?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);


	addToTextCache_AllAtOnce("Whoaa, you let the ", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("Night Gale", "assets\\fonts\\adrip1.ttf", 72, dinoRed);
	addToTextCache_AllAtOnce(" sweep you away?", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
	addToTextCache_AllAtOnce("Hold on tight next run!", "assets\\fonts\\adrip1.ttf", 72, snowWhite);
}