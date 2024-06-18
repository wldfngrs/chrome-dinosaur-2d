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
	void initDinoEntity();
	void initNonDinoEntities();
	void initObstacles();

	void resetNonDinoEntities();
	void resetDinoEntity();
	void resetObstacles();
	void resetGame();

	void showTitleScreen();
	void showGameOverScreen();

	void handleEvents();

	bool mInLobby;
	bool mPlayerQuit;
	bool mPlayerFail;
	bool mInitDone;

	std::string mGameOverMessage;
	std::string mInitErrorMessage;

	SDL_Window* mGameWindow;
	ObstacleManager mObstacleManager;
	TextManager mTextManager;

public:
	Game();
	~Game();

	void render();
	void update();
	void loop();

	bool initializationDone() const;
	bool playerHasQuit() const;

	TextManager& getTextManager();

	static int mTick;
	static int scale;
	static SDL_Event event;
	static SDL_Renderer* mGameRenderer;
	static EntityManager mEntityManager;

	static const int mSCREEN_WIDTH = 1280;
	static const int mSCREEN_HEIGHT = 720;
	static Entity& mDino;
};