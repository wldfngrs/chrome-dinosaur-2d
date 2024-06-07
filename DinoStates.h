#pragma once

#include "States.h"
#include "Sprites.h"

class RunningState : public DinoState {
	void enter(Dino& dino) override {
		if (!dino.jump && !dino.duck) {
			dino.setSrcRect(0, 32, 32, 32);

			dino.setDestRect
			(
				dino.transform->position.x,
				dino.transform->position.y + dino.jumpHeight,
				dino.transform->width,
				dino.transform->height
			);

			dino.mColliders.resize(2);

			/* HEAD */
			dino.setCollider(0, dino.transform->position.x + 12, dino.transform->position.y + 7, 14, 9);

			/* FRONT LEG/ARM */
			dino.setCollider(1, dino.transform->position.x + 16, dino.transform->position.y + 16, 7, 16);

			/* TAIL/TAILING LEG*/
			// dino.setCollider(2, dino.transform->position.x + 2, dino.transform->position.y + 16, 14, 12);
		}

		dino.setAnimation(0, 2, 150);
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

			/* HEAD */
			dino.setCollider(0, dino.transform->position.x + 16, dino.transform->position.y + 16, 15, 9);

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
	const int MAX_CHARGETIME = 10;

	bool landing = false;
	int landTime = 0;
	const int MAX_LANDTIME = 15;

	bool jumping = false;
	int jumpTime = 0;
	const int MAX_JUMPTIME = 30;

public:
	void enter(Dino& dino) override {
		dino.jump = true;
		if (!dino.duck) {
			dino.setSrcRect(0, 32, 32, 32);

			dino.setDestRect
			(
				dino.transform->position.x,
				dino.transform->position.y + dino.jumpHeight,
				dino.transform->width,
				dino.transform->height
			);

			dino.mColliders.resize(2);

			/* HEAD */
			dino.setCollider(0, dino.transform->position.x + 16, dino.transform->position.y + 9, 12, 7);

			/* TORSO */
			dino.setCollider(1, dino.transform->position.x + 8, dino.transform->position.y + 16, 14, 15);

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

				dino.mColliders.resize(2);

				/* HEAD */
				dino.setCollider(0, dino.transform->position.x + 16, dino.transform->position.y + 9, 13, 7);

				/* TORSO */
				dino.setCollider(1, dino.transform->position.x + 9, dino.transform->position.y + 16, 18, 8);

				//dino.setCollider(2, static_cast<int>(dino.transform->position.x), static_cast<int>(dino.transform->position.y + 21), 7, 12);
				//dino.mColliders[2].x = dino.transform->position.x;
				//dino.mColliders[2].y = dino.transform->position.y + 21;
				//dino.mColliders[2].w = 7;
				//dino.mColliders[2].h = 12;
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

				/* HEAD */
				dino.setCollider(0, dino.transform->position.x + 18, dino.transform->position.y + 19, 10, 9);

				// dino.mColliders[1].x = 10;
				// dino.mColliders[1].y = 31;
				// dino.mColliders[1].w = 11;
				// dino.mColliders[1].h = 1;
				// 
				// dino.mColliders[2].x = dino.transform->position.x;
				// dino.mColliders[2].y = dino.transform->position.y + 19;
				// dino.mColliders[2].w = 6;
				// dino.mColliders[2].h = 6;
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

		dino.state = new RunningState();
		dino.state->enter(dino);
		dino.jump = false;
	}
};