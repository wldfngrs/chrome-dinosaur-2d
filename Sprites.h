#pragma once

#include "TransformComponent.h"
#include "TextureManager.h"
#include "Collision.h"

class Sprite {
public:
	Collider collider;

	TransformComponent* transform;

	SDL_Rect srcRect, destRect;

	bool animated;
	int framesCount;
	int framesSpeed;

	int animIndex = 0;

	virtual void init() {}
	virtual void update() {}
	virtual void press_UP_key() {}
	virtual void press_DOWN_key() {}
	virtual void release_DOWN_key() {}

	void setAnimation(int index, int nFrames, int mSpeed) {
		animIndex = index;
		framesCount = nFrames;
		framesSpeed = mSpeed;
	}

	void setSrcRect(int x, int y, int w, int h) {
		srcRect.x = x;
		srcRect.y = y;
		srcRect.h = h;
		srcRect.w = w;
	}

	virtual void setDestRect(float x, float y, int w, int h) {
		transform->height = h;
		transform->width = w;
		transform->position.x = x;
		transform->position.y = y;
	}

	void setCollider(int colliderIndex, float x, float y, int w, int h) {
		collider.colliderRects[colliderIndex].x = static_cast<int>(x);
		collider.colliderRects[colliderIndex].y = static_cast<int>(y);
		collider.colliderRects[colliderIndex].w = w;
		collider.colliderRects[colliderIndex].h = h;
	}
};

class DinoState;

class Dino : public Sprite {
public:
	DinoState* state;

	bool jump = false;
	bool duck = false;

	const int jumpHeight = 290;

	void init() override;

	void update() override;

	void press_UP_key() override;

	void press_DOWN_key() override;

	void release_DOWN_key() override;

	void setDestRect(float x, float y, int w, int h) override;
};

class Background : public Sprite {
public:
	void init() override;

	void update() override;
};

class CelestialBody : public Sprite {
public:
	void update() override;
};

class Ground : public Sprite {
public:
	void init() override;

	void update() override;
};

class DyingTree1 : public Sprite {
public:
	void init() override;

	void update() override;
};

class DyingTree2 : public Sprite {
public:
	void init() override;

	void update() override;
};

class Bucket : public Sprite {
public:
	void init() override;

	void update() override;
};

class TreeStump : public Sprite {
public:
	void init() override;
	
	void update() override;
};

class Stalker : public Sprite {
public:
	void init() override;

	void update() override;
};

class Brute : public Sprite {
public:
	void init() override;

	void update() override;
};

class StalkerPup : public Sprite {
public:
	void init() override;
	
	void update() override;
};

class Gale : public Sprite {
public:
	void init() override;

	void update() override;
};