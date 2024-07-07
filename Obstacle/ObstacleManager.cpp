#include "ObstacleManager.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "EntityComponentSystem.h"
#include "Sprites.h"
#include "Game.h"
#include "Score.h"

#include <random>


void ObstacleManager::init() {
	mObstacles.resize(2);
	mObstaclesTransformCache.resize(2);
	mObstaclesSpriteCache.resize(2);

	for (size_t i = 0; i < mObstacles.size(); i++) {
		mObstacles[i] = &(Game::mEntityManager.addEntity());
		
		Entity& obstacle = *(mObstacles[i]);
		obstacle.addComponent<TransformComponent>();
		obstacle.addComponent<SpriteComponent>("Assets/textures/ObstacleSheet.png");

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

	updateMaxObstacleSpriteIndex();
	loadObstacles();
}

void ObstacleManager::update() {
	if (Game::mTick < 85) return;

	updateMaxObstacleSpriteIndex();
	updateObstacleSpeed();
	fieldObstacle();
	loadObstacles();
}

void ObstacleManager::updateMaxObstacleSpriteIndex() {
	int currentScore = Score::getCurrentScore();
	
	if (currentScore >= 700) {
		mMaxObstacleSpriteIndex = 7;
	} 
	else if (currentScore >= 500) {
		mMaxObstacleSpriteIndex = 5;
	}
	else if (currentScore >= 300) {
		mMaxObstacleSpriteIndex = 3;
	}
	else if (currentScore < 300) {
		mMaxObstacleSpriteIndex = 2;
	}
}

void ObstacleManager::updateObstacleSpeed() {
	for (size_t i = 0; i < mObstacles.size(); i++) {		
		if (mObstaclesTransformCache[i]->mPosition.x <= -mObstaclesTransformCache[i]->mWidth) {
			
			mObstaclesTransformCache[i]->mVelocity.zero();

		}
		else if (mObstaclesTransformCache[i]->mVelocity.x < 0 && mObstaclesTransformCache[i]->mPosition.x > Game::mSCREEN_WIDTH) {
			if (Game::mSpeedToggled) {
				mObstacleVelocity = -25;
				Game::mObstacleSpeedToggled = true;
			}
			else {
				mObstacleVelocity = -15;
				Game::mObstacleSpeedToggled = false;
			}

			mObstaclesTransformCache[i]->mVelocity.x = mObstacleVelocity;
		}
	}
}

void ObstacleManager::setDistanceBetweenObstacles(int seed) {
	if (Game::mSpeedToggled) seed = 2;

	if (seed <= 2) {
		mDistanceBetweenObstacles = 1280;
	}
	else if (seed <= 5) {
		mDistanceBetweenObstacles = 1000;
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
		spriteComponent->setSprite(std::make_unique<TreeStump>());
		break;
	case 3:
		spriteComponent->setSprite(std::make_unique<Bucket>());
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
			std::uniform_int_distribution<> indexDistr(0, mMaxObstacleSpriteIndex);
			std::uniform_int_distribution<> distDistr(0, 7);

			SpriteComponent* spriteComponent = mObstaclesSpriteCache[i];

			hotSwapObstacleSprite(spriteComponent, indexDistr(gen));

			mObstacles[i]->wakeUp();
			setDistanceBetweenObstacles(distDistr(gen));
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

	if (Score::getCurrentScore() + 30 >= Score::mGameCompletedScore) {
		return;
	}

	if (mObstaclesTransformCache[0]->mPosition.x == mObstaclesTransformCache[1]->mPosition.x) {
		
		mObstaclesTransformCache[0]->mVelocity.x = mObstacleVelocity;
	
	}
	
	if (abs(mObstaclesTransformCache[0]->mPosition.x - Game::mSCREEN_WIDTH) >= mDistanceBetweenObstacles && mObstaclesTransformCache[1]->mVelocity.x == 0) {

		mObstaclesTransformCache[1]->mVelocity.x = mObstacleVelocity;
	
	} else if (abs(mObstaclesTransformCache[1]->mPosition.x - Game::mSCREEN_WIDTH) >= mDistanceBetweenObstacles && mObstaclesTransformCache[0]->mVelocity.x == 0) {

		mObstaclesTransformCache[0]->mVelocity.x = mObstacleVelocity;
	
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

	spriteComponent->getSprite()->setTransform(static_cast<float>(3 * Game::mSCREEN_WIDTH / 4), static_cast<float>(Game::mSCREEN_HEIGHT / 7), 273, 275);
}