#pragma once

#include <vector>

class SpriteComponent;
class TransformComponent;
class Entity;

class ObstacleManager {
	std::vector<Entity*> obstacles;
	std::vector<TransformComponent*> obstaclesTransformData;
	std::vector<SpriteComponent*> obstaclesSpriteData;

	void loadObstacles();
	void fieldObstacle();
	void hotSwapObstacleSprite(SpriteComponent* spriteComponent, int sType);


public:
	ObstacleManager();

	void init();
	void reset();
	void update();
};