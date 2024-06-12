#include "TextureManager.h"

#include <sstream>

SDL_Texture* TextureManager::loadSpriteTexture(const char* pathToTexture) {
	SDL_Surface* tempSurface = IMG_Load(pathToTexture);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::gameRenderer, tempSurface);
	
	if (texture == nullptr) {
		std::stringstream ss;
		ss << "[Error] TextureManager::loadSpriteTexture(): '" << pathToTexture << "' SDL_CreateTextureFromSurface() failed!\nDetails: " << SDL_GetError() << "\n\n";
		Game::errorMessage = ss.str();
		Game::quit = true;

		throw std::runtime_error{ Game::errorMessage };
	}

	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::drawSprite(const char* pathToTexture, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	if (SDL_RenderCopy(Game::gameRenderer, texture, &src, &dest) < 0) {
		std::stringstream ss;
		ss << "[Error] TextureManager::drawSprite(): '" << pathToTexture << "', Texture: '"<< texture << "' SDL_RenderCopy() failed!\nDetails: " << SDL_GetError() << "\n\n";
		Game::errorMessage = ss.str();
		Game::quit = true;

		throw std::runtime_error{ Game::errorMessage };
	}
}

SDL_Texture* TextureManager::loadTextTexture(std::string textureText, TTF_Font* font, SDL_Color textColor) {
	SDL_Surface* tempSurface = TTF_RenderText_Blended(font, textureText.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::gameRenderer, tempSurface);

	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::getTextureWidthHeight(SDL_Texture* texture, int* width, int* height) {
	SDL_QueryTexture(texture, NULL, NULL, width, height);
}

void TextureManager::drawText(SDL_Texture* texture, int x, int y, int w, int h) {
	SDL_Rect dest = { x, y, w, h };
	SDL_RenderCopy(Game::gameRenderer, texture, NULL, &dest);
}