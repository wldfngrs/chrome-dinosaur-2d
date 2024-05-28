#pragma once

class DinoSprite;

class DinoState {
public:
	virtual void enter(DinoSprite& sprite) {}
	virtual void update(DinoSprite& sprite) {}
	virtual void leave(DinoSprite& sprite) {}
};