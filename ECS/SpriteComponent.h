#pragma once

#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "TextureManager.h"

#include <cstdarg>
#include <map>

class Sprite;

class SpriteComponent : public Component {
public:
	std::unique_ptr<Sprite> sprite;

	SpriteComponent(const char* pathToTexture, std::unique_ptr<Sprite> sprite, bool isAnimated, int x, int y, int w, int h);
	
	~SpriteComponent();

	void setTexture(const char* pathToTexture) const;

	void init() override;

	void update() override;

	void draw() override;
};