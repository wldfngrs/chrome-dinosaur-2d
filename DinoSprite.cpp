#include "Sprites.h"
#include "DinoStates.h"

void DinoSprite::init() {
	mColliders.resize(3);

	transform->entity->collidable = true;

	state = new RunningState();
	state->enter(*this);
}

void DinoSprite::update() {
	state->update(*this);

	if (transform->position.y >= 225) transform->position.y = 225;
}

void DinoSprite::press_UP_key() {
	state->leave(*this);

	if (state != nullptr) delete state;

	state = new JumpingState();

	duck = false;

	state->enter(*this);
}

void DinoSprite::press_DOWN_key() {
	if (!duck) {
		state->leave(*this);

		if (state != nullptr) delete state;

		state = new DuckingState();

		jump = false;

		state->enter(*this);
	}
}

void DinoSprite::release_DOWN_key() {
	state->leave(*this);

	if (state != nullptr) delete state;

	state = new RunningState();
	state->enter(*this);
}