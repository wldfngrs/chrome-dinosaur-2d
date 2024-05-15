#pragma once

#include "Game.h"
#include "Components.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	DinoComponent* dino;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		dino = &entity->getComponent<DinoComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_UP:
			case SDLK_SPACE:
				// dino jump
				//transform->position.y -= 100;
				dino->play("dinojump");
				break;
			case SDLK_DOWN:
				//transform->position.y += 100;// dino crouch
				//sprite->play("dinocrouch")
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_SPACE:
				// dino jump
				//transform->position.y -= 100;
				dino->play("dinorun");
				break;
			case SDLK_DOWN:
				transform->position.y = 225;
				// dino upright
				dino->play("dinorun");
				break;
			}
		}
	}
};