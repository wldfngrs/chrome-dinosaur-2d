#include "Game.h"
#include "TransformComponent.h"
#include "KeyboardController.h"
#include "Collision.h"
#include "SpriteComponent.h"
#include "ObstacleManager.h"
#include "Sprites.h"
#include "Text.h"
#include "Score.h"
#include <sstream>

int Game::mTick = 0;
SDL_Event Game::event;
SDL_Renderer* Game::mGameRenderer;
EntityManager Game::mEntityManager;

Entity& background(Game::mEntityManager.addEntity());
Entity& ground(Game::mEntityManager.addEntity());
Entity& celestialBody(Game::mEntityManager.addEntity());
Entity& Game::mDino(Game::mEntityManager.addEntity());

Game::Game() {
	if (initSDL() != 0) {
		return;
	}

	if (initFonts() != 0) {
		return;
	}
	
	initNonDinoEntities();
	
	initDinoEntity();
	
	initObstacles();
	
	Score::init();

	mInitDone = true;

	showTitleScreen();
}

Game::~Game() {
	SDL_DestroyWindow(mGameWindow);
	SDL_DestroyRenderer(mGameRenderer);

	mGameWindow = nullptr;
	mGameRenderer = nullptr;

	SDL_Quit();
	TTF_Quit();
}

int Game::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "[Error] Game::initSDL(): SDL_Init() failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	mGameWindow = SDL_CreateWindow("Dino 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mSCREEN_WIDTH, mSCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mGameWindow == nullptr) {
		std::cerr << "[Error] Game::initSDL(): SDL_CreateWindow() failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	mGameRenderer = SDL_CreateRenderer(mGameWindow, -1, 0);
	if (mGameRenderer == nullptr) {
		std::cerr << "[Error] Game::initSDL(): SDL_CreateRenderer() failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	return 0;
}

int Game::initFonts() {
	if (TTF_Init() < 0) {
		std::cerr << "[Error] Game::initTTF(): TTF_Init() failed!\nDetails: " << TTF_GetError() << "\n";
		return -1;
	}
	
	mTextManager.init();

	return 0;
}

void Game::showTitleScreen() {
	int time = 0;
	bool subtitleIsVisible = true;
	mInLobby = true;

	while (mInLobby) {
		SDL_SetRenderDrawColor(Game::mGameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(Game::mGameRenderer);

		mTextManager.drawText_Static("DINO SAUR", CENTERED, Game::mSCREEN_HEIGHT / 5, 80, 150);
		if (subtitleIsVisible) {
			mTextManager.drawText_Static("press [SPACE] to start", CENTERED, 360, 18, 40);
		}

		SDL_RenderPresent(Game::mGameRenderer);

		if (++time >= 400) {
			time = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}

		this->handleEvents();
	}
}

void Game::showGameOverScreen() {
	int tick = 0;
	bool subtitleIsVisible = true;

	mInLobby = true;

	int currScore = Score::getCurrentScore();

	if (currScore > Score::getHighScore()) {
		Score::setHighScore(currScore);
	}

	mObstacleManager.initGameOverAnimation();

	while (mInLobby) {
		SDL_SetRenderDrawColor(Game::mGameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(Game::mGameRenderer);

		mTextManager.drawText_Static_NonStatic("HIGH SCORE: ", std::to_string(Score::getHighScore()), CENTERED, 40, 24, 40);
		mTextManager.drawText_Static_NonStatic("CURRENT SCORE: ", std::to_string(Score::getCurrentScore()), CENTERED, 90, 24, 40);

		mObstacleManager.updateGameOverAnimation();

		mTextManager.drawText_Static(Game::mGameOverMessage, CENTERED, Game::mSCREEN_HEIGHT / 2 + Game::mSCREEN_HEIGHT / 5, 24, Game::mSCREEN_HEIGHT / 12);
		
		if (subtitleIsVisible) {
			mTextManager.drawText_Static("press [SPACE] to run again!", CENTERED, 640, 18, 40);
		}

		SDL_RenderPresent(Game::mGameRenderer);

		if (++tick >= 400) {
			tick = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}
			
		this->handleEvents();
	}
}

void Game::initNonDinoEntities() {
	background.addComponent<TransformComponent>(0, 0, Game::mSCREEN_WIDTH, Game::mSCREEN_HEIGHT - 80);
	background.addComponent<SpriteComponent>("assets\\sprites\\BackgroundSheet.png", std::make_unique<Background>(), 0, 64, 96, 64);
		
	celestialBody.addComponent<TransformComponent>(Game::mSCREEN_WIDTH, 150, 139, 130);
	celestialBody.addComponent<SpriteComponent>("assets\\sprites\\Moon.png", std::make_unique<CelestialBody>(), 0, 0, 28, 30);

	ground.addComponent<TransformComponent>(0, Game::mSCREEN_HEIGHT - 80, Game::mSCREEN_WIDTH, 80);
	ground.addComponent<SpriteComponent>("assets\\sprites\\GroundSheet.png", std::make_unique<Ground>(), 0, 0, 96, 16);
}

void Game::resetNonDinoEntities() {
	TransformComponent* transformComponent = &celestialBody.getComponent<TransformComponent>();
	transformComponent->mPosition.x = Game::mSCREEN_WIDTH;

	SpriteComponent* spriteComponent = &background.getComponent<SpriteComponent>();
	spriteComponent->getSprite()->setAnimation(1, 2, 500);
}

void Game::initDinoEntity() {
	mDino.addComponent<TransformComponent>(60, Game::mSCREEN_HEIGHT - 355, 273, 275);
	mDino.addComponent<SpriteComponent>("assets\\sprites\\DinoSheet.png", std::make_unique<Dino>(), 0, 0, 32, 32);
	mDino.addComponent<KeyboardController>();
}

void Game::resetDinoEntity() {
	SpriteComponent* spriteComponent = &mDino.getComponent<SpriteComponent>();

	spriteComponent->getSprite()->init();
}


void Game::initObstacles() {
	mObstacleManager.init();
}

void Game::resetObstacles() {
	mObstacleManager.reset();
}

void Game::resetGame() {
	resetNonDinoEntities();
	resetDinoEntity();
	resetObstacles();

	Score::reset();

	mPlayerFail = false;
	mTick = 0;
}

void Game::handleEvents() {
	SDL_PollEvent(&Game::event);

	switch (event.type) {
	case SDL_QUIT:
		mPlayerQuit = true;
		std::cout << "Dino 2D exited..." << std::endl;
		exit(0);
	case SDL_KEYDOWN:
		if (mInLobby && Game::event.key.keysym.sym == SDLK_SPACE) {
			mInLobby = false;
		}
		break;
	default:
		break;
	}
}

void Game::render() {
	SDL_RenderClear(Game::mGameRenderer);
	
	mEntityManager.draw();
	
	Score::draw(*this);

	SDL_RenderPresent(Game::mGameRenderer);
}

void Game::update() {
	mTick++;

	mObstacleManager.update();
	
	mEntityManager.refresh();
	mEntityManager.update();

	Score::update();

	if (Collision::checkForCollisions()) {
		mPlayerFail = true;
		Collision::mCollided = false;
		mGameOverMessage = Collision::getTag();
	}
}

void Game::loop() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (!mPlayerFail) {
		frameStart = SDL_GetTicks();
		
		handleEvents();
		update();
		render();
		
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
	showGameOverScreen();
	resetGame();
}

bool Game::initializationDone() const {
	return mInitDone;
}

bool Game::playerHasQuit() const {
	return mPlayerQuit;
}

TextManager& Game::getTextManager() {
	return mTextManager;
}