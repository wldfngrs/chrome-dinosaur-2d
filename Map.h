#pragma once

#include "Game.h"

class Map {
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* sky;

	int map[5][5];
public:
	Map();
	~Map();

	void loadMap(int arr[5][5]);
	void drawMap();

	static int row;
	static int col;
};