#include "Sprites.h"
#include "KeyboardController.h"
#include "DinoStates.h"

void Dino::init() {
	if (!animated) {
		animated = true;
	}
	
	transform->entity->collidable = true;

	state = new RunningState();
	state->enter(*this);
}

void Dino::update() {
	state->update(*this);
}

void Dino::press_UP_key() {
	if (!jump) {
		state->leave(*this);

		if (state != nullptr) delete state;

		state = new JumpingState();

		state->enter(*this);
	}
}

void Dino::press_DOWN_key() {
	if (!duck) {
		state->leave(*this);

		if (state != nullptr) delete state;

		state = new DuckingState();

		state->enter(*this);
	}
}

void Dino::release_DOWN_key() {
	state->leave(*this);

	if (state != nullptr) delete state;

	state = new RunningState();
	
	state->enter(*this);
}

void Dino::setDestRect(float x, float y, int w, int h) {
	transform->height = h;
	transform->width = w;
	transform->position.x = x;

	if (y > (Game::SCREEN_HEIGHT - 355)) {
		transform->position.y = Game::SCREEN_HEIGHT - 355;
	} else {
		transform->position.y = y;
	}
}