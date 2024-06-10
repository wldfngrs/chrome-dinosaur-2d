#pragma once

#include "SDL.h"

struct Collider {
	const char* tagOnCollision;
	std::vector<SDL_Rect> colliderRects;
};

class Collision {
public:
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B, const char* collisionTag);
	static void checkForCollision(Collider collider);
	static void checkForCollisions();
};