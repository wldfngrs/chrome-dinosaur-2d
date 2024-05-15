#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <cstdarg>
#include <map>

class DinoComponent : public Component {
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated;
	int frames = 0;
	int speed = 1;
	int airtime = 0; /*YOU DECLARED THIS VARIABLE, DON'T FORGET TO USE OR DELETE IT!*/

	char* currentplay;

	void setFrameCoords(Animation* animation, ...) {
		va_list coords;
		va_start(coords, animation->frames * 2);
		for (int i = 0; i < animation->frames; i++) {
			animation->framecoords[i].xpos = va_arg(coords, int);
			animation->framecoords[i].ypos = va_arg(coords, int);
		}
	}

public:

	int animIndex = 0;
	
	bool jump;

	std::map<const char*, Animation> animations;

	DinoComponent() = default;
	DinoComponent(const char* pathToTexture) {
		setTexture(pathToTexture);
	}

	DinoComponent(const char* pathToTexture, bool isAnimated) {
		animated = isAnimated;

		Animation dinorun = Animation(0, 2, 200);
		setFrameCoords(&dinorun, 100, 225, 60, 225);
		
		Animation dinojump = Animation(1, 3, 500);
		setFrameCoords(&dinojump, 60, 225, 60, 125, 60, 225);

		animations.emplace("dinorun", dinorun);
		animations.emplace("dinojump", dinojump);

		play("dinorun");

		setTexture(pathToTexture);
	}
	
	~DinoComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* pathToTexture) {
		texture = TextureManager::loadTexture(pathToTexture);
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.h = 32;
		srcRect.w = 32;
	}

	void update() override {
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
			srcRect.y = animIndex * srcRect.h;
		}

		destRect.x = (animated ? animations[currentplay].framecoords[animIndex].xpos : static_cast<int>(transform->position.x));
		destRect.y = (animated ? animations[currentplay].framecoords[animIndex].ypos : static_cast<int>(transform->position.y));
		destRect.w = transform->width;
		destRect.h = transform->height;
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}

	void play(const char* animName) {
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;

		currentplay = const_cast<char*>(animName);
	}
};