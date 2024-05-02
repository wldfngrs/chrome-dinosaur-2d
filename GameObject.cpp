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
	/*dstRect.h = 220;
	dstRect.w = 320;
	dstRect.x = 0;
	dstRect.y = 250;

	srcRect.x = xpos;
	srcRect.y = ypos;
	srcRect.w = dstRect.w * 2;
	srcRect.h = dstRect.h * 2;*/

	srcRect.h = 64;
	srcRect.w = 90;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = destRect.w * 2;
	destRect.h = destRect.h * 2;
}

int GameObject::render() {
	std::stringstream ss;
	if (SDL_RenderCopy(Game::renderer, this->objTexture, &(this->srcRect), &(this->destRect)) < 0) {
		ss << "GameObject::render() <-";
		this->errorMessage = ss.str();
		return -1;
	}

	return 0;
}

std::string GameObject::getErrorMessage() const {
	return this->errorMessage;
}