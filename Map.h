#pragma once

#include "Game.h"

class Map {
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* sky;

	int map[20][25];
public:
	Map();
	~Map();

	void loadMap(int arr[20][25]);
	void drawMap();
};