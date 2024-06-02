#pragma once

#include "EntityComponentSystem.h"
#include "Vector2D.h"

struct TransformComponent : public Component {
	Vector2D position;
	Vector2D velocity;

	int height = 1;
	int width = 1;
	int scale = 1;

	TransformComponent() {
		position.zero();
		velocity.zero();
	}

	TransformComponent(int scale) {
		position.zero();
		velocity.zero();
		this->scale = scale;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
		velocity.zero();
	}

	TransformComponent(float x, float y, int w, int h, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {}

	void update() override {
		position.x += velocity.x;
		position.y += velocity.y;
	}
};