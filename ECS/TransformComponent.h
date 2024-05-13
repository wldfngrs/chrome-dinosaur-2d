#pragma once

#include "Components.h"
#include "Vector2D.h"

struct TransformComponent : public Component {
	Vector2D position;
	Vector2D velocity;

	int height = 1;
	int width = 1;
	int scale = 1;

	int speed = 1;

	TransformComponent() {
		position.zero();
	}

	TransformComponent(int scale) {
		position.zero();
		this->scale = scale;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.zero();
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};