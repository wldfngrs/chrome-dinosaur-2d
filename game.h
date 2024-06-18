#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "EntityComponentSystem.h"
#include "ObstacleManager.h"
#include "Text.h"

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

	void showTitleScreen();
	void showGameOverScreen();

	bool inLobby;

	SDL_Window* gameWindow;

public:
	Game();
	~Game();

	void render();
	void update();
	void inGameLoop();
	void handleEvents();

	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	static std::string gameOverTag;

	bool initDone;

	static bool quit;
	static bool playerFail;

	static int tick;

	static std::string errorMessage;

	static SDL_Renderer* gameRenderer;

	static SDL_Event event;

	static EntityManager entityManager;
	static Entity& dino;

	static TextManager textManager;

	ObstacleManager obstacleManager;
};