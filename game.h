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

	ObstacleManager obstacleManager;
	TextManager textManager;
};