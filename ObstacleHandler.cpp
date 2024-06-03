#include "ObstacleHandler.h"
#include "Sprites.h"
#include "Game.h"

#include <random>

void ObstacleHandler::init() {
	obstacles.resize(2);
	obstaclesTransformData.resize(2);
	obstaclesSpriteData.resize(2);
}

void ObstacleHandler::addObstacle(Entity* obstacleEntity) {
	static int index = 0;

	obstacleEntity->destroy();
	obstacles[index] = obstacleEntity;
	obstaclesTransformData[index] = &obstacles[index]->getComponent<TransformComponent>();
	obstaclesSpriteData[index] = &obstacles[index]->getComponent<SpriteComponent>();
	index++;
}

void ObstacleHandler::hotSwapObstacleSprite(SpriteComponent* spriteComponent, int sType) {
	if (spriteComponent->sprite != nullptr) {
		spriteComponent->sprite.reset();
	}

	switch (sType) {
	case 0:
		spriteComponent->sprite = std::move(std::make_unique<DyingTree1>());
		break;
	case 1:
		spriteComponent->sprite = std::move(std::make_unique<DyingTree2>());
		break;
	case 2:
		spriteComponent->sprite = std::move(std::make_unique<Bucket>());
		break;
	case 3:
		spriteComponent->sprite = std::move(std::make_unique<TreeStump>());
		break;
	case 4:
		spriteComponent->sprite = std::move(std::make_unique<Stalker>());
		break;
	case 5:
		spriteComponent->sprite = std::move(std::make_unique<Brute>());
		break;
	case 6:
		spriteComponent->sprite = std::move(std::make_unique<StalkerPup>());
		break;
	case 7:
		spriteComponent->sprite = std::move(std::make_unique<Gale>());
		break;
	}

	spriteComponent->init();
}

void ObstacleHandler::loadObstacles() {
	for (auto i = 0; i < obstacles.size(); i++) {
		if (obstacles[i]->isInactive()) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distr(0, 7);

			SpriteComponent* spriteComponent = obstaclesSpriteData[i];

			hotSwapObstacleSprite(spriteComponent, distr(gen));

			obstacles[i]->wakeUp();
		}
	}
}

void ObstacleHandler::fieldObstacle() {
	for (auto i = 0; i < obstacles.size(); i++) {
		if (obstaclesTransformData[i]->position.x <= -obstaclesTransformData[i]->width) {
			obstacles[i]->destroy();
			return;
		}
	}

	if (obstaclesTransformData[0]->position.x == obstaclesTransformData[1]->position.x) {
		obstaclesTransformData[0]->position.x = Game::SCREEN_WIDTH + 101;
	}
	
	if (abs(obstaclesTransformData[0]->position.x - Game::SCREEN_WIDTH) >= 550 && obstaclesTransformData[1]->position.x == Game::SCREEN_WIDTH + 102) {
		obstaclesTransformData[1]->position.x = Game::SCREEN_WIDTH + 101;
	} else if (abs(obstaclesTransformData[1]->position.x - Game::SCREEN_WIDTH) >= 550 && obstaclesTransformData[0]->position.x == Game::SCREEN_WIDTH + 102) {
		obstaclesTransformData[0]->position.x = Game::SCREEN_WIDTH + 101;
	}
}