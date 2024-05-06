#include "Map.h"
#include "TextureManager.h"

int lvl1[5][5] = {
	{0,0,0,0,0},
	{1,0,0,1,0},
	{0,1,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
};

int Map::row = 5;
int Map::col = 5;

Map::Map() {
	this->dirt = TextureManager::loadTexture("assets\\Classic\\cloud_day.png");
	this->grass = TextureManager::loadTexture("assets\\Classic\\cloud_day.png");
	this->sky = TextureManager::loadTexture("assets\\Classic\\cloud_day.png");

	loadMap(lvl1);

	src.x = src.y = 0;
	dest.x = dest.y = 0;

	src.w = dest.w = 180;
	src.h = dest.h = 96;
}

Map::~Map() {
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(sky);
	SDL_DestroyTexture(dirt);
}

void Map::loadMap(int arr[5][5]) {
	for (int row = 0; row < Map::row; row++) {
		for (int col = 0; col < Map::col; col++) {
			map[row][col] = arr[row][col];
		}
	}
}

void Map::drawMap() {
	int type = 0;
	for (int row = 0; row < Map::row; row++) {
		for (int col = 0; col < Map::col; col++) {
			type = map[row][col];

			dest.x = col * 180;
			dest.y = row * 96;

			switch (type) {
			case 0:
				break;
				TextureManager::draw(dirt, src, dest);
				break;
			case 1:
				TextureManager::draw(grass, src, dest);
				break;
			case 2:
				TextureManager::draw(sky, src, dest);
				break;
			default:
				break;
			}
		}
	}
}