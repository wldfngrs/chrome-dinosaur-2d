#include "Game.h"
#include "Collision.h"
#include "TransformComponent.h"
#include "EntityComponentSystem.h"
#include "Sprites.h"
#include "SpriteComponent.h"

bool Collision::AABB(const SDL_Rect& A, const SDL_Rect& B, const char* collisionTag) {
	if (A.x + A.w >= B.x
		&&
		B.x + B.w >= A.x
		&&
		A.y + A.h >= B.y
		&&
		B.y + B.h >= A.y)
	{
		Game::gameOverTag = collisionTag;
		Game::playerFail = true;
		return true;
	}
	
	return false;
}

void Collision::checkForCollision(Collider otherCollider) {
	Collider& dinoCollider = Game::dino.getComponent<SpriteComponent>().getSprite()->getCollider();
		
	for (auto& p : dinoCollider.getColliderRects()) {
		for (auto& c : otherCollider.getColliderRects()) {
			if (AABB(p, c, otherCollider.getCollisionTag())) {
				return;
			}
		}
	}
}

void Collision::checkForCollisions() {
	EntityManager& eManager = Game::dino.getEntityManager();
	std::vector<std::unique_ptr<Entity>>& entities = eManager.getEntities();
	
	/* Check for collision between Game::dino and the other game entities, only if they are collidable i.e Obstacles */

	for (auto& e : entities) {
		if (e->isActive() && (Game::dino.mEntityIndex != e->mEntityIndex)) {
			checkForCollision(e->getComponent<SpriteComponent>().getSprite()->getCollider());
		}
	}
}