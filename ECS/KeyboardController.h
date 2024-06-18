#pragma once

#include "EntityComponentSystem.h"
#include "../Game.h"
#include "SpriteComponent.h"
#include "Sprites.h"

class KeyboardController : public Component {
	SpriteComponent* mSpriteComponent;

public:
	void init() override {
		mSpriteComponent = &mEntity->getComponent<SpriteComponent>();
	}

	void update() override {
		if ((Game::event.type == SDL_KEYDOWN)) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_SPACE:
				mSpriteComponent->getSprite()->press_UP_key();
				break;

			case SDLK_DOWN:
				mSpriteComponent->getSprite()->press_DOWN_key();
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_DOWN:
				mSpriteComponent->getSprite()->release_DOWN_key();
				break;
			}
		}
	}
};