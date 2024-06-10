#include "ObstacleHandler.h"
#include "Sprites.h"
#include "Game.h"

#include <random>

std::vector<Entity*> ObstacleHandler::obstacles;
std::vector<TransformComponent*> ObstacleHandler::obstaclesTransformData;
std::vector<SpriteComponent*> ObstacleHandler::obstaclesSpriteData;

void ObstacleHandler::init() {
	obstacles.resize(2);
	obstaclesTransformData.resize(2);
	obstaclesSpriteData.resize(2);

	for (auto i = 0; i < obstacles.size(); i++) {
		obstacles[i] = &(Game::entityManager.addEntity());
		
		Entity& obstacle = *(obstacles[i]);
		obstacle.addComponent<TransformComponent>();
		obstacle.addComponent<SpriteComponent>("assets\\sprites\\ObstacleSheet.png");

		obstacle.destroy();
		obstaclesTransformData[i] = &obstacle.getComponent<TransformComponent>();
		obstaclesSpriteData[i] = &obstacle.getComponent<SpriteComponent>();
	}

	loadObstacles();
}

void ObstacleHandler::reset() {
	for (auto i = 0; i < obstacles.size(); i++) {
		Entity& obstacle = *(obstacles[i]);
		obstacle.destroy();
		obstacle.getComponent<TransformComponent>().velocity.zero();
	}

	loadObstacles();
}

void ObstacleHandler::update() {
	if (Game::tick < 105) return;

	fieldObstacle();
	loadObstacles();
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
	
	if (abs(obstaclesTransformData[0]->position.x - Game::SCREEN_WIDTH) >= 900 && obstaclesTransformData[1]->position.x == Game::SCREEN_WIDTH + 102) {
		obstaclesTransformData[1]->position.x = Game::SCREEN_WIDTH + 101;
	} else if (abs(obstaclesTransformData[1]->position.x - Game::SCREEN_WIDTH) >= 900 && obstaclesTransformData[0]->position.x == Game::SCREEN_WIDTH + 102) {
		obstaclesTransformData[0]->position.x = Game::SCREEN_WIDTH + 101;
	}
}