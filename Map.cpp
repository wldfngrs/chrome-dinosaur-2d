#include "Map.h"
#include "TextureManager.h"

int lvl1[8][6] = {
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0},
	{0,0,0,0,0,0}
};

int Map::row = 8;
int Map::col = 6;

Map::Map() {
	this->dirt = TextureManager::loadTexture("assets\\Classic\\cloud1.png");
	this->grass = TextureManager::loadTexture("assets\\Classic\\cloud1.png");
	this->sky = TextureManager::loadTexture("assets\\Classic\\cloud1.png");

	loadMap(lvl1);

	src.x = src.y = 0;
	src.w = dest.w = 150;
	src.h = dest.h = 60;

	dest.x = dest.y = 0;
}

Map::~Map() {}

void Map::loadMap(int arr[8][6]) {
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

			dest.x = col * 150;
			dest.y = row * 60;

			switch (type) {
			case 0:
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