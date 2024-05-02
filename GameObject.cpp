#include "GameObject.h"
#include "TextureManager.h"

#include <sstream>

GameObject::GameObject(const char* pathToTexture, int x, int y) {
	this->objTexture = TextureManager::loadTexture(pathToTexture);
	this->xpos = x;
	this->ypos = y;
}

GameObject::~GameObject() {}

void GameObject::update() {
	destRect.h = 110;
	destRect.w = 100;
	destRect.x = 60;
	destRect.y = 310;

	srcRect.x = xpos;
	srcRect.y = ypos;
	srcRect.w = destRect.w * 2;
	srcRect.h = destRect.h * 2;
}

void GameObject::render() {
	if (SDL_RenderCopy(Game::renderer, this->objTexture, &(this->srcRect), &(this->destRect)) < 0) {
		std::stringstream ss;
		ss << "[ERROR] GameObject::render(): SDL_RenderCopy() Failed!\nDetails: " << SDL_GetError() << "\n\n";
		Game::running = false;
		Game::errorMessage = ss.str();
	}
}