#include "Game.h"
#include "TransformComponent.h"
#include "KeyboardController.h"
#include "Collision.h"
#include "SpriteComponent.h"
#include "ObstacleManager.h"
#include "DirtManager.h"
#include "Sprites.h"
#include "Text.h"
#include "Score.h"

#include "SDL_ttf.h"
#include "SDL.h"

#include <sstream>

int Game::mTick = 0;
bool Game::mSpeedToggled = false;
bool Game::mObstacleSpeedToggled = false;
bool Game::mGameCompleted = false;

SDL_Event Game::mEvent;
SDL_Renderer* Game::mGameRenderer;
EntityManager Game::mEntityManager;
SoundManager Game::mSoundManager;

Entity& background(Game::mEntityManager.addEntity());
Entity& celestialBody(Game::mEntityManager.addEntity());
Entity& Game::mDino(Game::mEntityManager.addEntity());

Game::Game() {
	if (initSDL() != 0) {
		return;
	}

	if (initFonts() != 0) {
		return;
	}

	if (initSounds() != 0) {
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
	Mix_Quit();
}

int Game::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
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
		std::cerr << "[Error] Game::initFonts(): TTF_Init() failed!\nDetails: " << TTF_GetError() << "\n";
		return -1;
	}
	
	mTextManager.init();

	return 0;
}

int Game::initSounds() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		std::cerr << "[Error] Game::initSounds() Couldn't initialize SDL Mixer!\n";
		return -1;
	}

	mSoundManager.init();

	return 0;
}

void Game::showTitleScreen() {
	int visibilityTick = 0;
	bool subtitleIsVisible = true;
	mInLobby = true;

	mSoundManager.playMusic(LOBBY_MUSIC);

	while (mInLobby) {
		SDL_SetRenderDrawColor(Game::mGameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(Game::mGameRenderer);

		mTextManager.drawText_Static("DINO SAUR", CENTERED, Game::mSCREEN_HEIGHT / 5, 80, 150, INSTANT);
		if (subtitleIsVisible) {
			mTextManager.drawText_Static("press [SPACE] to start", CENTERED, 360, 18, 40, INSTANT);
		}

		mTextManager.drawText_Static("a 2D remake of the classic Chrome dinosaur game\nby wldfngrs; https://github.com/wldfngrs", CENTERED, 628, 12, 26, INSTANT);

		SDL_RenderPresent(Game::mGameRenderer);

		if (++visibilityTick >= 400) {
			visibilityTick = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}
		
		handleEvents();
	}
}

void Game::showGameOverScreen() {
	int visibilityTick = 0;
	bool subtitleIsVisible = true;

	mSoundManager.playMusic(LOBBY_MUSIC);

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

		mTextManager.drawText_Static(Game::mGameOverMessage, CENTERED, 400, 24, Game::mSCREEN_HEIGHT / 14, INSTANT);
		
		if (subtitleIsVisible) {
			mTextManager.drawText_Static("press [SPACE] to run again, [ALT + F4] to quit...", CENTERED, 600, 18, 40, INSTANT);
		}

		SDL_RenderPresent(Game::mGameRenderer);

		if (++visibilityTick >= 400) {
			visibilityTick = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}
		
		handleEvents();
	}
}

void Game::showGameCompletedScreen() {
	int visibilityTick = 0;
	bool subtitleIsVisible = true;

	mInLobby = true;

	mSoundManager.playMusic(LOBBY_MUSIC);

	SDL_SetRenderDrawColor(Game::mGameRenderer, 0, 0, 0, 0);
	SDL_RenderClear(Game::mGameRenderer);
	
	mTextManager.drawText_Static("Congratulations! You beat the game!\n"
								 "It's no big deal, and certainly no difficult task, yet...\n\n"
								 "I appreciate you for playing this long\n"
								 "I had fun working on this. I hope you had fun playing as well\n"
								 "Have a great day, anon!", CENTERED, 80, 20, 40, TYPEWRITER);

	SDL_Rect subtitleRect = { 0, 600, 1280, Game::mSCREEN_HEIGHT - 600 };

	SDL_PumpEvents();
	SDL_FlushEvent(SDL_QUIT);
	SDL_FlushEvent(SDL_KEYDOWN);

	while (mInLobby) {
		SDL_RenderFillRect(Game::mGameRenderer, &subtitleRect);

		if (subtitleIsVisible) {
			mTextManager.drawText_Static("press [SPACE] to run again, [ALT + F4] to quit...", CENTERED, 600, 18, 40, INSTANT);
		}

		SDL_RenderPresent(Game::mGameRenderer);

		if (++visibilityTick >= 400) {
			visibilityTick = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}

		handleEvents();
	}
}

void Game::initNonDinoEntities() {
	background.addComponent<TransformComponent>(0, 0, Game::mSCREEN_WIDTH, Game::mSCREEN_HEIGHT - 80);
	background.addComponent<SpriteComponent>("assets\\sprites\\BackgroundSheet.png", std::make_unique<Background>(), 0, 64, 96, 64);
		
	celestialBody.addComponent<TransformComponent>(Game::mSCREEN_WIDTH, 150, 139, 130);
	celestialBody.addComponent<SpriteComponent>("assets\\sprites\\Moon.png", std::make_unique<CelestialBody>(), 0, 0, 28, 30);

	mDirtManager.init();
}

void Game::resetNonDinoEntities() {
	TransformComponent* transformComponent = &celestialBody.getComponent<TransformComponent>();
	transformComponent->mPosition.x = Game::mSCREEN_WIDTH;

	SpriteComponent* spriteComponent = &background.getComponent<SpriteComponent>();
	spriteComponent->getSprite()->setAnimation(1, 2, 500);

	Background* background = (Background*)spriteComponent->getSprite().get();
	background->resetTick();
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
	Score::reset();

	resetNonDinoEntities();
	resetDinoEntity();
	resetObstacles();

	mPlayerFail = false;
	mSpeedToggled = false;
	mObstacleSpeedToggled = false;

	mTick = 0;
}

void Game::handleEvents() {
	SDL_PollEvent(&Game::mEvent);

	switch (mEvent.type) {
	case SDL_QUIT:
		mPlayerQuit = true;
		std::cout << "Dino 2D exited..." << std::endl;
		exit(0);
	case SDL_KEYDOWN:
		if (mInLobby && (Game::mEvent.key.keysym.sym == SDLK_SPACE || Game::mEvent.key.keysym.sym == SDLK_UP)) {
			mInLobby = false;
			mGameCompleted = false;
		}
		
		break;
	default:
		break;
	}
}

void Game::render() {
	SDL_RenderClear(Game::mGameRenderer);
	
	mEntityManager.draw();

	mDirtManager.draw();
	
	Score::draw(*this);

	SDL_RenderPresent(Game::mGameRenderer);
}

void Game::update() {
	mTick++;

	Score::update();

	mObstacleManager.update();
	
	mEntityManager.refresh();
	mEntityManager.update();

	mDirtManager.update();

	if (Collision::checkForCollisions()) {
		mSoundManager.playSound(SND_COLLISION, CH_DINO);
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

	mSoundManager.playMusic(MORNING_MUSIC);

	while (!mPlayerFail && !mGameCompleted) {
		frameStart = SDL_GetTicks();
		
		handleEvents();
		update();
		render();
		
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	
	if (mPlayerFail) {
		showGameOverScreen();
	}
	else if (mGameCompleted) {
		showGameCompletedScreen();
	}

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