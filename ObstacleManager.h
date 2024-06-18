#pragma once

#include <vector>

class SpriteComponent;
struct TransformComponent;
class Entity;

class ObstacleManager {
	int mJustCollidedIndex;

	std::vector<Entity*> mObstacles;
	std::vector<TransformComponent*> mObstaclesTransformCache;
	std::vector<SpriteComponent*> mObstaclesSpriteCache;

	void loadObstacles();
	void fieldObstacle();
	void hotSwapObstacleSprite(SpriteComponent* spriteComponent, int sType);

public:
	void init();
	void reset();
	void update();

	void updateGameOverAnimation();
	void initGameOverAnimation();
};