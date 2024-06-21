#pragma once

#include <vector>

class SpriteComponent;
struct TransformComponent;
class Entity;

class ObstacleManager {
	int mJustCollidedIndex;
	int mDistanceBetweenObstacles;

	int mObstacleVelocity = -15;

	std::vector<Entity*> mObstacles;
	std::vector<TransformComponent*> mObstaclesTransformCache;
	std::vector<SpriteComponent*> mObstaclesSpriteCache;

	void loadObstacles();
	void fieldObstacle();
	void updateObstaclePosition();
	void hotSwapObstacleSprite(SpriteComponent* spriteComponent, int sType);
	void setDistanceBetweenObstacles(int seed);

public:
	void init();
	void reset();
	void update();

	void updateGameOverAnimation();
	void initGameOverAnimation();
};