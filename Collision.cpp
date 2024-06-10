#include "Game.h"
#include "Collision.h"
#include "TransformComponent.h"
#include "EntityComponentSystem.h"
#include "Sprites.h"
#include "SpriteComponent.h"

bool Collision::AABB(const SDL_Rect& A, const char* Atag, const SDL_Rect& B, const char* Btag) {
	if (A.x + A.w >= B.x
		&&
		B.x + B.w >= A.x
		&&
		A.y + A.h >= B.y
		&&
		B.y + B.h >= A.y)
	{
		std::cout << Atag << " hit " << Btag << std::endl;
		std::cout << "Game Over!" << std::endl;
		Game::playerFail = true;
		return true;
	}
	
	return false;
}

void Collision::checkForCollision(std::vector<std::pair<const char*, SDL_Rect>> colliders) {
	std::vector<std::pair<const char*, SDL_Rect>>& dinoColliders = Game::dino.getComponent<SpriteComponent>().sprite->mColliders;
		
	for (auto& p : dinoColliders) {
		for (auto& c : colliders) {
			if (AABB(p.second, p.first, c.second, c.first)) {
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
		if (e->isActive() && e->collidable && (Game::dino.entityIndex != e->entityIndex)) {
			checkForCollision(e->getComponent<SpriteComponent>().sprite->mColliders);
		}
	}
}