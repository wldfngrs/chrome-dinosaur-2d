#pragma once

#include <vector>

#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class ObstacleHandler {
	std::vector<Entity*> obstacles;
	std::vector<TransformComponent*> obstaclesTransformData;
	std::vector<SpriteComponent*> obstaclesSpriteData;

public:
	void init();
	void loadObstacles();
	void fieldObstacle();
	void addObstacle(Entity* obstacleEntity);
	void hotSwapObstacleSprite(SpriteComponent* spriteComponent, int sType);
};