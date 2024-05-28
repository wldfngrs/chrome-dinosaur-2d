#pragma once

#include "TransformComponent.h"
#include "TextureManager.h"

class Sprite {
public:
	SDL_Texture* texture;

	char* pathToTexture;

	TransformComponent* transform;
	SDL_Rect srcRect, destRect;

	bool animated;
	int frames;
	int speed;

	int animIndex = 0;

	virtual void init() {}
	virtual void update() {}
	virtual void press_UP_key() {}
	virtual void press_DOWN_key() {}
	virtual void release_DOWN_key() {}

	void setAnimation(int index, int nFrames, int mSpeed) {
		animIndex = index;
		frames = nFrames;
		speed = mSpeed;
	}

	void setSrcRect(int x, int y, int w, int h) {
		srcRect.x = x;
		srcRect.y = y;
		srcRect.h = h;
		srcRect.w = w;
	}

	void setDestRect(int x, int y, int w, int h) {
		transform->height = h;
		transform->width = w;
		transform->position.x = static_cast<float>(x);
		transform->position.y = static_cast<float>(y);
	}
};

class DinoState;

class DinoSprite : public Sprite {
public:
	DinoState* state;

	bool jump = false;
	bool duck = false;

	void init() override;

	void update() override;

	void press_UP_key() override;

	void press_DOWN_key() override;

	void release_DOWN_key() override;
};

class BackgroundSprite : public Sprite {
public:
	void init() override;

	void update() override;
};

class CelestialBodySprite : public Sprite {
public:
	void update() override;
};

class GroundSprite : public Sprite {
public:
	void init() override;

	void update() override;
};