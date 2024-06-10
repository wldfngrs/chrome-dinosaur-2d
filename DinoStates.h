#pragma once

#include "States.h"
#include "Sprites.h"

class RunningState : public DinoState {
	void enter(Dino& dino) override {
		if (!dino.jump && !dino.duck) {
			dino.setSrcRect(0, 0, 32, 32);

			dino.setDestRect
			(
				dino.transform->position.x,
				dino.transform->position.y + dino.jumpHeight,
				dino.transform->width,
				dino.transform->height
			);

			dino.mColliders.resize(1);
			dino.setCollider(0, "Dino", dino.transform->position.x, dino.transform->position.y + 59, 221, 213);

			dino.setAnimation(0, 2, 150);
		}
	}

	void update(Dino& dino) override {
		if (dino.animated) {
			dino.srcRect.x = dino.srcRect.w * static_cast<int>((SDL_GetTicks() / dino.framesSpeed) % dino.framesCount);
			dino.srcRect.y = dino.animIndex * dino.srcRect.h;
		}
	}

	void leave(Dino& dino) override {}
};

class DuckingState : public DinoState {
	void enter(Dino& dino) override {
		if (!dino.duck && !dino.jump) {
			dino.setSrcRect(0, 64, 32, 32);

			dino.setDestRect
			(
				dino.transform->position.x,
				dino.transform->position.y + dino.jumpHeight,
				dino.transform->width,
				dino.transform->height
			);

			dino.mColliders.resize(1);
			dino.setCollider(0, "Dino",dino.transform->position.x, dino.transform->position.y + 136, 273, 136);

			dino.duck = true;

			dino.setAnimation(2, 2, 200);
		}
	}

	void update(Dino& dino) override {
		if (dino.animated) {
			dino.srcRect.x = dino.srcRect.w * static_cast<int>((SDL_GetTicks() / dino.framesSpeed) % dino.framesCount);
			dino.srcRect.y = dino.animIndex * dino.srcRect.h;
		}
	}

	void leave(Dino& dino) override {
		if (dino.duck) dino.duck = false;
	}
};

class JumpingState : public DinoState {
	bool charging = false;
	int chargeTime = 0;
	const int MAX_CHARGETIME = 5;

	bool landing = false;
	int landTime = 0;
	const int MAX_LANDTIME = 13;

	bool jumping = false;
	int jumpTime = 0;
	const int MAX_JUMPTIME = 30;

public:
	void enter(Dino& dino) override {
		dino.jump = true;
		if (!dino.duck) {
			dino.setSrcRect(0, 32, 32, 32);

			dino.mColliders.resize(1);
			dino.setCollider(0, "Dino",dino.transform->position.x + 8, dino.transform->position.y + 76, 230, 196);

			charging = true;
		}
	}

	void update(Dino& dino) override {
		if (charging) {
			chargeTime++;

			if (chargeTime >= MAX_CHARGETIME) {
				chargeTime = 0;
				charging = false;
				jumping = true;
				dino.setSrcRect(32, 32, 32, 32);

				dino.setDestRect
				(
					dino.transform->position.x,
					dino.transform->position.y - dino.jumpHeight,
					dino.transform->width,
					dino.transform->height
				);

				dino.mColliders.resize(1);
				dino.setCollider(0, "Dino",-1, -1, -1, -1);
			}
		}


		if (jumping) {
			jumpTime++;

			if (jumpTime >= MAX_JUMPTIME) {
				jumpTime = 0;
				jumping = false;
				landing = true;
				dino.setSrcRect(64, 32, 32, 32);

				dino.setDestRect
				(
					dino.transform->position.x,
					dino.transform->position.y + dino.jumpHeight,
					dino.transform->width,
					dino.transform->height
				);

				dino.mColliders.resize(1);
				dino.setCollider(0, "Dino",dino.transform->position.x, dino.transform->position.y + 315, 255, 119);
			}
		}

		if (landing) {
			landTime++;

			if (landTime >= MAX_LANDTIME) {
				landing = false;
				landTime = 0;
				leave(dino);
			}
		}
	}

	void leave(Dino& dino) override {
		if (dino.state != nullptr) delete dino.state;

		dino.jump = false;
		dino.state = new RunningState();
		dino.state->enter(dino);
	}
};