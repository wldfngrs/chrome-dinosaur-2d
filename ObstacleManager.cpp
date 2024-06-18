#include "ObstacleManager.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "EntityComponentSystem.h"
#include "Sprites.h"
#include "Game.h"

#include <random>


void ObstacleManager::init() {
	mObstacles.resize(2);
	mObstaclesTransformData.resize(2);
	mObstaclesSpriteData.resize(2);

	for (size_t i = 0; i < mObstacles.size(); i++) {
		mObstacles[i] = &(Game::entityManager.addEntity());
		
		Entity& obstacle = *(mObstacles[i]);
		obstacle.addComponent<TransformComponent>();
		obstacle.addComponent<SpriteComponent>("assets\\sprites\\ObstacleSheet.png");

		obstacle.destroy();
		mObstaclesTransformData[i] = &obstacle.getComponent<TransformComponent>();
		mObstaclesSpriteData[i] = &obstacle.getComponent<SpriteComponent>();
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
	if (Game::tick < 90) return;

	fieldObstacle();
	loadObstacles();
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

			SpriteComponent* spriteComponent = mObstaclesSpriteData[i];

			hotSwapObstacleSprite(spriteComponent, distr(gen));

			mObstacles[i]->wakeUp();
		}
	}
}

void ObstacleManager::fieldObstacle() {
	for (size_t i = 0; i < mObstacles.size(); i++) {
		if (mObstaclesTransformData[i]->mPosition.x <= -mObstaclesTransformData[i]->mWidth) {
			mObstacles[i]->destroy();
			return;
		}
	}

	if (mObstaclesTransformData[0]->mPosition.x == mObstaclesTransformData[1]->mPosition.x) {
		
		mObstaclesTransformData[0]->mPosition.x = Game::SCREEN_WIDTH + 101;
	
	}
	
	if (abs(mObstaclesTransformData[0]->mPosition.x - Game::SCREEN_WIDTH) >= 900 && mObstaclesTransformData[1]->mPosition.x == Game::SCREEN_WIDTH + 102) {
		
		mObstaclesTransformData[1]->mPosition.x = Game::SCREEN_WIDTH + 101;
	
	} else if (abs(mObstaclesTransformData[1]->mPosition.x - Game::SCREEN_WIDTH) >= 900 && mObstaclesTransformData[0]->mPosition.x == Game::SCREEN_WIDTH + 102) {
		
		mObstaclesTransformData[0]->mPosition.x = Game::SCREEN_WIDTH + 101;
	
	}
}

void ObstacleManager::updateGameOverAnimation() {
	mObstacles[mJustCollidedIndex]->update();
	mObstacles[mJustCollidedIndex]->draw();

	mObstaclesTransformData[mJustCollidedIndex]->mVelocity.x = (float)(- 0.4);

	if (mObstaclesTransformData[mJustCollidedIndex]->mPosition.x <= (Game::SCREEN_WIDTH / 4 - mObstaclesTransformData[mJustCollidedIndex]->mWidth)) {
		mObstaclesTransformData[mJustCollidedIndex]->mPosition.x = static_cast<float>(3 * Game::SCREEN_WIDTH / 4);
	}
}

void ObstacleManager::initGameOverAnimation() {
	if (mObstaclesTransformData[0]->mPosition.x < mObstaclesTransformData[1]->mPosition.x) {
		mJustCollidedIndex = 0;
	}
	else {
		mJustCollidedIndex = 1;
	}

	SpriteComponent* spriteComponent = &mObstacles[mJustCollidedIndex]->getComponent<SpriteComponent>();

	spriteComponent->getSprite()->setTransform(static_cast<float>(3 * Game::SCREEN_WIDTH / 4), static_cast<float>(Game::SCREEN_HEIGHT / 4), 273, 275);
}