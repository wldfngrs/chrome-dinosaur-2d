#pragma once

#include "EntityComponentSystem.h"
#include "ObstacleManager.h"
#include "DirtManager.h"
#include "SoundManager.h"
#include "Text.h"

#include <iostream>
#include <string>
#include <vector>

class Entity;

class Game {
	int initSDL();
	int initFonts();
	int initSounds();
	void initDinoEntity();
	void initNonDinoEntities();
	void initObstacles();

	void resetNonDinoEntities();
	void resetDinoEntity();
	void resetObstacles();
	void resetGame();

	void showTitleScreen();
	void showGameOverScreen();
	void showGameCompletedScreen();

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
	DirtManager mDirtManager;

public:
	Game();
	~Game();

	void render();
	void update();
	void loop();

	bool initializationDone() const;
	bool playerHasQuit() const;

	TextManager& getTextManager();


	static bool mSpeedToggled;
	static bool mGameCompleted;

	static int mTick;
	static SDL_Event mEvent;
	static SDL_Renderer* mGameRenderer;
	static EntityManager mEntityManager;
	static SoundManager mSoundManager;

	static const int mSCREEN_WIDTH = 1280;
	static const int mSCREEN_HEIGHT = 720;

	static Entity& mDino;
};