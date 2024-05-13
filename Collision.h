#pragma once

#include "SDL.h"

class ColliderComponent;

class Collision {
public:
	static bool AABB(const SDL_Rect& A, const SDL_Rect& B); // Axis-Aligned Bounding Box
	static bool AABB(const ColliderComponent& A, const ColliderComponent& B);
};