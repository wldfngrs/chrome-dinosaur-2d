#include "Collision.h"
#include "ColliderComponent.h"

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

bool Collision::AABB(const ColliderComponent& A, const ColliderComponent& B) {
	if (A.tag == "dino" && B.tag == "ground") {
		if (A.collider.y + A.collider.h >= B.collider.y) {
			A.entity->getComponent<TransformComponent>().position.y = 225;
			return true;
		}
	}

	if (AABB(A.collider, B.collider)) {
		std::cout << A.tag << " hit " << B.tag << std::endl;
		return true;
	}

	return false;
}