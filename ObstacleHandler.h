#pragma once

#include <vector>

#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class ObstacleHandler {
	static std::vector<Entity*> obstacles;
	static std::vector<TransformComponent*> obstaclesTransformData;
	static std::vector<SpriteComponent*> obstaclesSpriteData;

public:
	static void init();
	static void reset();
	static void update();
	static void loadObstacles();
	static void fieldObstacle();
	static void hotSwapObstacleSprite(SpriteComponent* spriteComponent, int sType);
};