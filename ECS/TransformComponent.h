#pragma once

#include "Components.h"
#include "Vector2D.h"

struct TransformComponent : public Component {
	Vector2D position;
	Vector2D velocity;

	int height = 110;
	int width = 100;
	int scale = 1;

	int speed = 3;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(int scale) {
		position.x = 0.0f;
		position.y = 0.0f;
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
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};