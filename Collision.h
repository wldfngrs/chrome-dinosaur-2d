#pragma once

#include "SDL.h"

class Collision {
public:
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B);
	static void checkForCollision(std::vector<SDL_Rect> colliders);
	static void checkForCollisions();
};