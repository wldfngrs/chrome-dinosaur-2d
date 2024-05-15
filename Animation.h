#pragma once

#include <vector>

struct Frame {
	int xpos;
	int ypos;
};

struct Animation {
	int index;
	int frames;
	int speed;
	std::vector<Frame> framecoords;

	Animation() {};
	Animation(int i, int f, int s) {
		index = i;
		frames = f;
		speed = s;
		framecoords.resize(frames);
	}
};