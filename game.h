#pragma once

#include "SDL.h"

#include <iostream>
#include <string>

class Game {
public:
	Game();
	~Game();

	void handleEvents();
	void render();
	void update();
	void mainLoop();
	
	bool isRunning() const { return running; }

	static bool initError;

private:
	int initGame();
	void closeGame();

	static bool running;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window;
	SDL_Renderer* renderer;
};