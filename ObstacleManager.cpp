#include "ObstacleManager.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "EntityComponentSystem.h"
#include "Sprites.h"
#include "Game.h"

#include <random>


void ObstacleManager::init() {
	mObstacles.resize(2);
	mObstaclesTransformCache.resize(2);
	mObstaclesSpriteCache.resize(2);

	for (size_t i = 0; i < mObstacles.size(); i++) {
		mObstacles[i] = &(Game::mEntityManager.addEntity());
		
		Entity& obstacle = *(mObstacles[i]);
		obstacle.addComponent<TransformComponent>();
		obstacle.addComponent<SpriteComponent>("assets\\sprites\\ObstacleSheet.png");

		obstacle.destroy();
		mObstaclesTransformCache[i] = &obstacle.getComponent<TransformComponent>();
		mObstaclesSpriteCache[i] = &obstacle.getComponent<SpriteComponent>();
	}

	loadObstacles();
}

void ObstacleManager::reset() {
	for (size_t i = 0; i < mObstacles.size(); i++) {
		Entity& obstacle = *(mObstacles[i]);
		obstacle.destroy();
		obstacle.getComponent<TransformComponent>().mVelocity.zero();
	}

	loadObstacles();
}

void ObstacleManager::update() {
	if (Game::mTick < 85) return;

	updateObstaclePosition();
	fieldObstacle();
	loadObstacles();
}

void ObstacleManager::updateObstaclePosition() {
	for (size_t i = 0; i < mObstacles.size(); i++) {		
		if (mObstaclesTransformCache[i]->mPosition.x <= -mObstaclesTransformCache[i]->mWidth) {
			
			mObstaclesTransformCache[i]->mVelocity.zero();

		} else if (mObstaclesTransformCache[i]->mPosition.x <= Game::mSCREEN_WIDTH + 101) {
			
			mObstaclesTransformCache[i]->mVelocity.x = static_cast<float>(mObstacleVelocity);
		}
	}
}

void ObstacleManager::setDistanceBetweenObstacles(int seed) {
	if (seed <= 2) {
		mDistanceBetweenObstacles = 1000;
	}
	else if (seed <= 5) {
		mDistanceBetweenObstacles = 900;
	}
	else if (seed <= 7) {
		mDistanceBetweenObstacles = 800;
	}
}

void ObstacleManager::hotSwapObstacleSprite(SpriteComponent* spriteComponent, int sType) {
	switch (sType) {
	case 0:
		spriteComponent->setSprite(std::make_unique<DyingTree1>());
		break;
	case 1:
		spriteComponent->setSprite(std::make_unique<DyingTree2>());
		break;
	case 2:
		spriteComponent->setSprite(std::make_unique<Bucket>());
		break;
	case 3:
		spriteComponent->setSprite(std::make_unique<TreeStump>());
		break;
	case 4:
		spriteComponent->setSprite(std::make_unique<Stalker>());
		break;
	case 5:
		spriteComponent->setSprite(std::make_unique<Brute>());
		break;
	case 6:
		spriteComponent->setSprite(std::make_unique<StalkerPup>());
		break;
	case 7:
		spriteComponent->setSprite(std::make_unique<Gale>());
		break;
	}

	spriteComponent->init();
}

void ObstacleManager::loadObstacles() {
	for (size_t i = 0; i < mObstacles.size(); i++) {
		if (mObstacles[i]->isInactive()) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distr(0, 7);

			SpriteComponent* spriteComponent = mObstaclesSpriteCache[i];

			hotSwapObstacleSprite(spriteComponent, distr(gen));

			mObstacles[i]->wakeUp();
			setDistanceBetweenObstacles(distr(gen));
		}
	}
}

void ObstacleManager::fieldObstacle() {
	for (size_t i = 0; i < mObstacles.size(); i++) {
		if (mObstaclesTransformCache[i]->mPosition.x <= -mObstaclesTransformCache[i]->mWidth) {
			
			mObstacles[i]->destroy();
			return;
		
		}
	}

	if (mObstaclesTransformCache[0]->mPosition.x == mObstaclesTransformCache[1]->mPosition.x) {
		
		mObstaclesTransformCache[0]->mPosition.x = Game::mSCREEN_WIDTH + 101;
	
	}
	
	if (abs(mObstaclesTransformCache[0]->mPosition.x - Game::mSCREEN_WIDTH) >= mDistanceBetweenObstacles && mObstaclesTransformCache[1]->mPosition.x == Game::mSCREEN_WIDTH + 102) {

		mObstaclesTransformCache[1]->mPosition.x = Game::mSCREEN_WIDTH + 101;
	
	} else if (abs(mObstaclesTransformCache[1]->mPosition.x - Game::mSCREEN_WIDTH) >= mDistanceBetweenObstacles && mObstaclesTransformCache[0]->mPosition.x == Game::mSCREEN_WIDTH + 102) {

		mObstaclesTransformCache[0]->mPosition.x = Game::mSCREEN_WIDTH + 101;
	
	}
}

void ObstacleManager::updateGameOverAnimation() {
	mObstacles[mJustCollidedIndex]->update();
	mObstacles[mJustCollidedIndex]->draw();

	mObstaclesTransformCache[mJustCollidedIndex]->mVelocity.x = (float)(- 0.4);

	if (mObstaclesTransformCache[mJustCollidedIndex]->mPosition.x <= (Game::mSCREEN_WIDTH / 4 - mObstaclesTransformCache[mJustCollidedIndex]->mWidth)) {
		
		mObstaclesTransformCache[mJustCollidedIndex]->mPosition.x = static_cast<float>(3 * Game::mSCREEN_WIDTH / 4);
	
	}
}

void ObstacleManager::initGameOverAnimation() {
	if (mObstaclesTransformCache[0]->mPosition.x < mObstaclesTransformCache[1]->mPosition.x) {
		
		mJustCollidedIndex = 0;
	
	}
	else {
		
		mJustCollidedIndex = 1;
	
	}

	SpriteComponent* spriteComponent = &mObstacles[mJustCollidedIndex]->getComponent<SpriteComponent>();

	spriteComponent->getSprite()->setTransform(static_cast<float>(3 * Game::mSCREEN_WIDTH / 4), static_cast<float>(Game::mSCREEN_HEIGHT / 4), 273, 275);
}