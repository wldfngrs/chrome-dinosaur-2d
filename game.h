#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Font.h"

#include <iostream>
#include <string>
#include <vector>

class Entity;

class Game {
	int initSDL();
	int initFonts();
	int initEntities();
	int initObstacles();
	bool showTitleScreen() const;


	SDL_Window* gameWindow;

public:
	Game();
	~Game();

	void render();
	void update();
	void inGameLoop();
	void handleEvents() const;

	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	bool initDone;

	static bool quit;
	static bool playerFail;

	static std::string errorMessage;

	static SDL_Renderer* gameRenderer;

	std::unique_ptr<Font> gameTitle;
	std::unique_ptr<Font> gameSubtitle;

	static SDL_Event event;

	static Entity& player;
};