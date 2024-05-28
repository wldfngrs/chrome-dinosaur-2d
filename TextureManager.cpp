#include "TextureManager.h"

#include <sstream>

SDL_Texture* TextureManager::loadTexture(const char* pathToTexture) {
	SDL_Surface* tempSurface = IMG_Load(pathToTexture);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	if (texture == nullptr) {
		std::stringstream ss;
		ss << "[Error] TextureManager::loadTexture(): PathToTexture: " << pathToTexture << " SDL_CreateTextureFromSurface() Failed!\nDetails: " << SDL_GetError() << "\n\n";
		Game::errorMessage = ss.str();
		Game::running = false;
	}

	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::draw(const char* pathToTexture, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	if (SDL_RenderCopy(Game::renderer, texture, &src, &dest) < 0) {
		std::stringstream ss;
		ss << "[ERROR] TextureManager::draw(): PathToTexture: '" << pathToTexture << "', Texture: '"<< texture << "' SDL_RenderCopy() Failed!\nDetails: " << SDL_GetError() << "\n\n";
		Game::errorMessage = ss.str();
		Game::running = false;
	}
}