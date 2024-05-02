#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "GameObject.h"

#include <iostream>
#include <string>
#include <utility>

class Game {
	int initGame();
	void closeGame();

	static bool running;

	const int SCREEN_WIDTH = 900;
	const int SCREEN_HEIGHT = 480;

	std::string errorMessage;

	SDL_Window* window;

public:
	Game();
	~Game();

	void handleEvents();
	void render();
	void update();
	void mainLoop();

	std::string getErrorMessage();

	bool isRunning() const { return running; }

	static bool initError;
	static SDL_Renderer* renderer;
};