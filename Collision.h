#pragma once

#include "SDL.h"

class Collider {
	const char* mCollisionTag;
	std::vector<SDL_Rect> mColliderRects;

public:
	void resize(size_t newSize) {
		mColliderRects.resize(newSize);
	}

	void setColliderRect(int colliderIndex, int x, int y, int w, int h) {
		mColliderRects[colliderIndex].x = x;
		mColliderRects[colliderIndex].y = y;
		mColliderRects[colliderIndex].w = w;
		mColliderRects[colliderIndex].h = h;
	}

	std::vector<SDL_Rect> getColliderRects() const {
		return mColliderRects;
	}

	void setCollisionTag(const char* collisionTag) {
		mCollisionTag = collisionTag;
	}

	const char* getCollisionTag() const {
		return mCollisionTag;
	}
};

class Collision {
public:
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B, const char* collisionTag);
	static void checkForCollision(Collider collider);
	static void checkForCollisions();
};