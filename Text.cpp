#include "Text.h"
#include "Game.h"
#include "TextureManager.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

TextManager::TextManager() {}

TextManager::~TextManager() {
	for (auto& t : textCache) {
		SDL_DestroyTexture(t.second);
	}

	textCache.clear();
}

void TextManager::extractTextSegments(std::vector<std::string>& textSegments, std::vector<int>& textLineLen, std::string text) {
	int delimitingIndex;
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

	auto start = delimitingIndex + delimitingText.size();
	auto next = start;

	auto lineindex = 0;

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

void TextManager::drawTextSegments(std::vector<std::string> segments, std::vector<int> lineLen, int x, int y, int letterWidth, int letterHeight) {
	auto spacing = 0;
	auto lineLenIndex = 0;

	int w = segments[0].size() * letterWidth;
	int h = letterHeight;

	if (x == CENTERED) x = Game::SCREEN_WIDTH / 2 - lineLen[lineLenIndex++] * letterWidth / 2;
	
	TextureManager::drawText(textCache[segments[0]], x, y, w, h);

	for (auto i = 1; i < segments.size(); i++) {
		if (segments[i] == "\\n") {
			y += (h + 2);
			x = Game::SCREEN_WIDTH /2 - lineLen[lineLenIndex++] * letterWidth / 2;
			w = segments[++i].size() * letterWidth;
			TextureManager::drawText(textCache[segments[i]], x, y, w, h);
		}
		else {
			x += w;
			w = segments[i].size() * letterWidth;
			TextureManager::drawText(textCache[segments[i]], x, y, w, h);
		}
	}
}

void TextManager::drawText(std::string text, int x, int y, int letterWidth, int letterHeight, bool isStatic) {
	if (isStatic) {
		std::vector<std::string> textSegments;
		std::vector<int> textLineLen;
		extractTextSegments(textSegments, textLineLen, text);

		drawTextSegments(textSegments, textLineLen, x, y, letterWidth, letterHeight);
	}
	else {
		auto numSpaces = 8 - text.size();
		int spacing = 1;

		for (auto i = 0; i < numSpaces; i++) {
			TextureManager::drawText(textCache[" "], x, y, letterWidth, letterHeight);
			x = x + letterWidth + spacing;
		}

		for (auto t : text) {
			std::string txt;
			txt += text[0];
			TextureManager::drawText(textCache[txt], x, y, letterWidth, letterHeight);
			x = x + letterWidth + spacing;
		}
	}
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

void TextManager::init() {
	SDL_Color dinoRed = { 184, 37, 53 };
	SDL_Color snowWhite = { 255, 255, 255 };
	addToTextCache("DINO SAUR", "assets\\fonts\\Marshland_Beauty.otf", 72, dinoRed, true);
	addToTextCache("press [SPACE] to start", "assets\\fonts\\ALBA____.TTF", 36, snowWhite, true);

	addToTextCache("HIGH SCORE", "assets\\fonts\\ALBA____.TTF", 12, snowWhite, true);
	addToTextCache("CURRENT SCORE", "assets\\fonts\\ALBA____.TTF", 12, snowWhite, true);
	addToTextCache("0123456789", "assets\\fonts\\ALBA____.TTF", 12, snowWhite, false);
	addToTextCache(" ", "assets\\fonts\\ALBA____.TTF", 12, snowWhite, true);

	addToTextCache("Sh*t! caught in the ", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Dying Trees", "assets\\fonts\\adrip1.ttf", 72, dinoRed, true);
	addToTextCache("!", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Wriggle out for your next run?", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);

	addToTextCache("Danmit! You've kicked ", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("The Bucket", "assets\\fonts\\adrip1.ttf", 72, dinoRed, true);
	addToTextCache("Did I mention you have nine (ahem) lives?", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);

	addToTextCache("Oof! crashed right into a ", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Tree Stump", "assets\\fonts\\adrip1.ttf", 72, dinoRed, true);
	//addToTextCache("!", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Watch your path, Rex.", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);

	addToTextCache("Hehe, the one-eyed ", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Stalker", "assets\\fonts\\adrip1.ttf", 72, dinoRed, true);
	addToTextCache("...", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Look away next time, okay?", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);

	addToTextCache("Yikes, ", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Stalker Pups", "assets\\fonts\\adrip1.ttf", 72, dinoRed, true);
	//addToTextCache("...", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Nothing to see or say here, Rex, run again?", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);

	addToTextCache("Ouch, crushed by the merciless ", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Brute", "assets\\fonts\\adrip1.ttf", 72, dinoRed, true);
	addToTextCache("Oh well, you're not THAT hurt, go again?", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);


	addToTextCache("Whoaa, you let the ", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Night Gale", "assets\\fonts\\adrip1.ttf", 72, dinoRed, true);
	addToTextCache(" sweep you away?", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);
	addToTextCache("Hold on tight next run!", "assets\\fonts\\adrip1.ttf", 72, snowWhite, true);

}

void TextManager::update() {}

//void TextManager::drawAtStandardPosition(std::string text, int position, int w, int h, bool isStatic) {
////	   .__________________________________________________________.
////	   |LEFT & UP			    UP & CENTER				RIGHT & UP|
////	   |														  |
////	   |														  |
////	   |LEFT & CENTER			 CENTER				RIGHT & CENTER|
////	   |														  |
////	   |														  |
////	   |LEFT & DOWN_____________UP & DOWN_____________RIGHT & DOWN|
//
//	int x(0), y(0);
//
//	if (((position & LEFT) && (position & RIGHT)) || ((position & UP) && (position & DOWN)) || ((position & LEFT) && (position & UP))) {
//		x = 0;
//		y = 0;
//	}
//
//	else if ((position & LEFT) && (position & CENTER)) {
//		x = 0;
//		y = Game::SCREEN_HEIGHT / 2 - h/2;
//	}
//
//	else if ((position & LEFT) && (position & DOWN)) {
//		x = 0;
//		y = Game::SCREEN_HEIGHT - h;
//	}
//
//	else if ((position & UP) && (position & CENTER)) {
//		x = Game::SCREEN_WIDTH / 2 - w/2;
//		y = 0;
//	}
//
//	else if ((position & DOWN) && (position & CENTER)) {
//		x = Game::SCREEN_WIDTH / 2 - w/2;
//		y = Game::SCREEN_HEIGHT;
//	}
//
//	else if ((position & RIGHT) && (position & UP)) {
//		x = Game::SCREEN_WIDTH - w;
//		y = 0;
//	}
//
//	else if ((position & RIGHT) && (position & CENTER)) {
//		x = Game::SCREEN_WIDTH - w;
//		y = Game::SCREEN_HEIGHT / 2 - h/2;
//	}
//
//	else if ((position & RIGHT) && (position & DOWN)) {
//		x = Game::SCREEN_WIDTH - w;
//		y = Game::SCREEN_HEIGHT - h;
//	}
//
//	else if ((position & CENTER)) {
//		x = Game::SCREEN_WIDTH / 2 - w / 2;
//		y = Game::SCREEN_HEIGHT / 2 - h / 2;
//	}
//
//	draw(text, x, y, w, h, isStatic);
//}