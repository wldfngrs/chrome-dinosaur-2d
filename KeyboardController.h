#pragma once

#include "Game.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_SPACE:
				// dino jump
				transform->velocity.y = -10;
				break;
			case SDLK_DOWN:
				transform->velocity.y = +10;// dino crouch
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_SPACE:
				// dino jump
				transform->velocity.y = 0;
				break;
			case SDLK_DOWN:
				transform->velocity.y = 0;// dino upright
				break;
			}
		}
	}
};