#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <string>
#include <vector>

class EntityManager;
class Entity;

class Game {
	int initGame();
	void closeGame();

	SDL_Window* window;

public:
	Game();
	~Game();

	void render();
	void update();
	void mainLoop();
	void handleEvents();

	static const int SCREEN_WIDTH = 900;
	static const int SCREEN_HEIGHT = 480;

	static bool initError;
	static bool running;
	
	static std::string errorMessage;

	static SDL_Renderer* renderer;
	static SDL_Event event;

	static Entity& player;
};