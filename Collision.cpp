#include "Collision.h"

bool Collision::AABB(const SDL_Rect& A, const SDL_Rect& B) {
	if (A.x + A.w >= B.x
		&&
		B.x + B.w >= A.x
		&&
		A.y + A.h >= B.y
		&&
		B.y + B.h >= A.y)
	{
		return true;
	}
	
	return false;
}