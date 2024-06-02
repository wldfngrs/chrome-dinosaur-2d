#include "Sprites.h"
#include "KeyboardController.h"
#include "DinoStates.h"

void Dino::init() {
	transform->entity->collidable = true;

	state = new RunningState();
	state->enter(*this);
}

void Dino::update() {
	state->update(*this);

	if (transform->position.y > 225) {
		transform->position.y = 225;
	}
}

void Dino::press_UP_key() {
	if (!jump) {
		state->leave(*this);

		if (state != nullptr) delete state;

		state = new JumpingState();

		duck = false;

		state->enter(*this);
	}
}

void Dino::press_DOWN_key() {
	if (!duck) {
		state->leave(*this);

		if (state != nullptr) delete state;

		state = new DuckingState();

		jump = false;

		state->enter(*this);
	}
}

void Dino::release_DOWN_key() {
	state->leave(*this);

	if (state != nullptr) delete state;

	state = new RunningState();
	state->enter(*this);
}