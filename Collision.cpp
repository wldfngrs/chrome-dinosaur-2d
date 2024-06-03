#include "Game.h"
#include "Collision.h"
#include "TransformComponent.h"
#include "EntityComponentSystem.h"
#include "Sprites.h"
#include "SpriteComponent.h"

bool Collision::AABB(const SDL_Rect& A, const SDL_Rect& B) {
	if (A.x + A.w >= B.x
		&&
		B.x + B.w >= A.x
		&&
		A.y + A.h >= B.y
		&&
		B.y + B.h >= A.y)
	{
		std::cout << "Collision happened!" << std::endl;
		return true;
	}
	
	return false;
}

void Collision::checkForCollision(std::vector<SDL_Rect> colliders) {
	std::vector<SDL_Rect>& dinoColliders = Game::player.getComponent<SpriteComponent>().sprite->mColliders;
		
	for (auto& p : dinoColliders) {
		for (auto& c : colliders) {
			AABB(p, c);
		}
	}
}

void Collision::checkForCollisions() {
	EntityManager& eManager = Game::player.getEntityManager();
	std::vector<std::unique_ptr<Entity>>& entities = eManager.getEntities();
	
	/* Check for collision between Game::dino and the other game entities, only if they are collidable i.e Obstacles */

	for (auto& e : entities) {
		if (e->collidable && (Game::player.entityIndex != e->entityIndex) && e->isActive()) {
			checkForCollision(e->getComponent<SpriteComponent>().sprite->mColliders);
		}
	}
}