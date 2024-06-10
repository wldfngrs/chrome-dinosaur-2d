#pragma once

#include "SDL.h"

class Collision {
public:
	static bool AABB(const SDL_Rect& A, const char* Atag, const SDL_Rect& B, const char* Btag);
	static void checkForCollision(std::vector<std::pair<const char*, SDL_Rect>> colliders);
	static void checkForCollisions();
};