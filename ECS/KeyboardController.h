#pragma once

#include "EntityComponentSystem.h"
#include "../Game.h"
#include "SpriteComponent.h"
#include "Sprites.h"

class KeyboardController : public Component {
public:
	SpriteComponent* spriteComponent;

	void init() override {
		spriteComponent = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if ((Game::event.type == SDL_KEYDOWN)) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_SPACE:
				spriteComponent->sprite->press_UP_key();
				break;

			case SDLK_DOWN:
				spriteComponent->sprite->press_DOWN_key();
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_DOWN:
				spriteComponent->sprite->release_DOWN_key();
				break;
			}
		}
	}
};