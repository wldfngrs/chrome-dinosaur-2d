#pragma once

#include "EntityComponentSystem.h"
#include "TextureManager.h"

#include <cstdarg>
#include <map>

class Sprite;

class SpriteComponent : public Component {
	SDL_Texture* texture;
	const char* pathToTexture;
public:
	std::unique_ptr<Sprite> sprite;

	SpriteComponent(const char* pathToTexture, std::unique_ptr<Sprite> sprite, bool isAnimated, int x, int y, int w, int h);
	SpriteComponent(const char* pathToTexture);

	~SpriteComponent();

	void setTexture(const char* pathToTexture);

	void init() override;

	void update() override;

	void draw() override;
};