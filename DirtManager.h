#pragma once

#include "SDL.h"
#include "Vector2D.h"

#include <vector>
#include <utility>

struct Dirt {
	int x;
	int y;
	int mWidth;
	int mHeight;

	Dirt(int xpos, int ypos, int w, int h) : x(xpos), y(ypos), mWidth(w), mHeight(h) {}
};

class DirtManager {
	int mDirtVelocity = -15;

	SDL_Texture* mTexture;

	SDL_Rect mSrcRectGround;
	SDL_Rect mSrcRectDirt;

	SDL_Rect mDestRectGround;
	SDL_Rect mDestRectDirt;

	std::vector<Dirt> mDirt;

	void setRect(SDL_Rect& rect, int x, int y, int w, int h);
	void setTexture();

	int generateDirtLen(int seed);

	bool isPositionOccupied(int x, int y);

public:
	void init();
	void update();
	void draw();
};