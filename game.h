#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "GameObject.h"

#include <iostream>
#include <string>

class Game {
	int initGame();
	void closeGame();

	const int SCREEN_WIDTH = 900;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window;

public:
	Game();
	~Game();

	void handleEvents();
	void render();
	void update();
	void mainLoop();

	static bool initError;
	static bool running;
	
	static std::string errorMessage;

	static SDL_Renderer* renderer;
	static SDL_Event event;
};