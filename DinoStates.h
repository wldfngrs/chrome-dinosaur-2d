#pragma once

#include "States.h"
#include "Sprites.h"

class RunningState : public DinoState {
	void enter(DinoSprite& dino) override {
		if (!dino.jump && !dino.duck) {
			dino.setSrcRect(0, 32, 32, 32);

			dino.setDestRect
			(
				dino.transform->position.x,
				dino.transform->position.y + 150,
				dino.transform->width,
				dino.transform->height
			);

			dino.mColliders[0].x = dino.transform->position.x + 12;
			dino.mColliders[0].y = dino.transform->position.y + 7;
			dino.mColliders[0].w = 14;
			dino.mColliders[0].h = 9;

			dino.mColliders[1].x = dino.transform->position.x + 16;
			dino.mColliders[1].y = dino.transform->position.y + 16;
			dino.mColliders[1].w = 7;
			dino.mColliders[1].h = 16;

			dino.mColliders[2].x = dino.transform->position.x + 2;
			dino.mColliders[2].y = dino.transform->position.y + 16;
			dino.mColliders[2].w = 14;
			dino.mColliders[2].h = 12;
		}

		dino.setAnimation(0, 2, 150);
	}

	void update(DinoSprite& dino) override {
		if (dino.animated) {
			dino.srcRect.x = dino.srcRect.w * static_cast<int>((SDL_GetTicks() / dino.speed) % dino.frames);
			dino.srcRect.y = dino.animIndex * dino.srcRect.h;
		}
	}

	void leave(DinoSprite& dino) override {}
};

class DuckingState : public DinoState {
	void enter(DinoSprite& dino) override {
		if (!dino.duck && !dino.jump) {
			dino.setSrcRect(0, 64, 32, 32);

			dino.setDestRect
			(
				dino.transform->position.x,
				dino.transform->position.y + 150,
				dino.transform->width,
				dino.transform->height
			);

			dino.mColliders[0].x = dino.transform->position.x + 16;
			dino.mColliders[0].y = dino.transform->position.y + 16;
			dino.mColliders[0].w = 14;
			dino.mColliders[0].h = 9;

			dino.mColliders[1].x = dino.transform->position.x + 16;
			dino.mColliders[1].y = dino.transform->position.y + 31;
			dino.mColliders[1].w = 7;
			dino.mColliders[1].h = 1;

			dino.mColliders[2].x = dino.transform->position.x + 1;
			dino.mColliders[2].y = dino.transform->position.y + 21;
			dino.mColliders[2].w = 6;
			dino.mColliders[2].h = 13;

			dino.duck = true;

			dino.setAnimation(2, 2, 200);
		}
	}

	void update(DinoSprite& dino) override {
		if (dino.animated) {
			dino.srcRect.x = dino.srcRect.w * static_cast<int>((SDL_GetTicks() / dino.speed) % dino.frames);
			dino.srcRect.y = dino.animIndex * dino.srcRect.h;
		}
	}

	void leave(DinoSprite& dino) override {
		if (dino.duck) dino.duck = false;
	}
};

class JumpingState : public DinoState {
	bool charge = false;
	int chargeTime = 0;
	const int MAX_CHARGETIME = 10;

	bool land = false;
	int landTime = 0;
	const int MAX_LANDTIME = 15;

	int jumpTime = 0;
	const int MAX_JUMPTIME = 20;

public:
	void enter(DinoSprite& dino) override {
		if (!dino.jump && !dino.duck) {
			dino.setSrcRect(0, 32, 32, 32);

			dino.setDestRect
			(
				dino.transform->position.x,
				dino.transform->position.y + 150,
				dino.transform->width,
				dino.transform->height
			);

			dino.mColliders[0].x = dino.transform->position.x + 16;
			dino.mColliders[0].y = dino.transform->position.y + 9;
			dino.mColliders[0].w = 12;
			dino.mColliders[0].h = 7;

			dino.mColliders[1].x = dino.transform->position.x + 8;
			dino.mColliders[1].y = dino.transform->position.y + 16;
			dino.mColliders[1].w = 14;
			dino.mColliders[1].h = 15;

			dino.mColliders[2].x = dino.transform->position.x + 1;
			dino.mColliders[2].y = dino.transform->position.y + 21;
			dino.mColliders[2].w = 7;
			dino.mColliders[2].h = 5;

			charge = true;
		}
	}

	void update(DinoSprite& dino) override {
		if (charge) {
			chargeTime++;

			if ((chargeTime >= MAX_CHARGETIME)) {
				chargeTime = 0;
				charge = false;
				dino.jump = true;
				dino.setSrcRect(32, 32, 32, 32);

				dino.setDestRect
				(
					dino.transform->position.x,
					dino.transform->position.y - 150,
					dino.transform->width,
					dino.transform->height
				);

				dino.mColliders[0].x = dino.transform->position.x + 16;
				dino.mColliders[0].y = dino.transform->position.y + 9;
				dino.mColliders[0].w = 13;
				dino.mColliders[0].h = 7;

				dino.mColliders[1].x = dino.transform->position.x + 8;
				dino.mColliders[1].y = dino.transform->position.y + 16;
				dino.mColliders[1].w = 18;
				dino.mColliders[1].h = 13;

				dino.mColliders[2].x = dino.transform->position.x;
				dino.mColliders[2].y = dino.transform->position.y + 21;
				dino.mColliders[2].w = 7;
				dino.mColliders[2].h = 12;
			}
		}


		if (dino.jump) {
			jumpTime++;

			if ((jumpTime >= MAX_JUMPTIME)) {
				jumpTime = 0;
				dino.jump = false;
				land = true;
				dino.setSrcRect(64, 32, 32, 32);

				dino.setDestRect
				(
					dino.transform->position.x,
					dino.transform->position.y + 150,
					dino.transform->width,
					dino.transform->height
				);

				dino.mColliders[0].x = dino.transform->position.x + 18;
				dino.mColliders[0].y = dino.transform->position.y + 19;
				dino.mColliders[0].w = 10;
				dino.mColliders[0].h = 9;

				dino.mColliders[1].x = 10;
				dino.mColliders[1].y = 31;
				dino.mColliders[1].w = 11;
				dino.mColliders[1].h = 1;

				dino.mColliders[2].x = dino.transform->position.x;
				dino.mColliders[2].y = dino.transform->position.y + 19;
				dino.mColliders[2].w = 6;
				dino.mColliders[2].h = 6;
			}
		}

		if (land) {
			landTime++;

			if (landTime >= MAX_LANDTIME && !dino.jump) {
				land = false;
				landTime = 0;
				leave(dino);
			}
		}
	}

	void leave(DinoSprite& dino) override {
		if (dino.state != nullptr) delete dino.state;

		dino.state = new RunningState();
		dino.state->enter(dino);
	}
};