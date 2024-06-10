#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Font.h"
#include "EntityComponentSystem.h"

#include <iostream>
#include <string>
#include <vector>

class Entity;

class Game {
	int initSDL();
	int initFonts();
	int initDinoEntity();
	int initNonDinoEntities();
	int initObstacles();

	void resetNonDinoEntities();
	void resetDinoEntity();
	void resetObstacles();
	void resetGame();

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

	static int tick;

	static std::string errorMessage;

	static SDL_Renderer* gameRenderer;

	std::unique_ptr<Font> gameTitle;
	std::unique_ptr<Font> gameSubtitle;

	static SDL_Event event;

	static EntityManager entityManager;
	static Entity& dino;
};