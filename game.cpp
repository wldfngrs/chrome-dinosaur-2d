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

SDL_Event Game::event;
bool Game::quit = false;
bool Game::playerFail = false;
std::string Game::gameOverTag;
std::string Game::errorMessage;
SDL_Renderer* Game::gameRenderer;
TextManager Game::textManager;

int Game::tick = 0;

EntityManager Game::entityManager;

Entity& map(Game::entityManager.addEntity());
Entity& ground(Game::entityManager.addEntity());
Entity& celestialBody(Game::entityManager.addEntity());
Entity& Game::dino(Game::entityManager.addEntity());

Game::Game() {
	if (initSDL() != 0) {
		return;
	}

	if (initFonts() != 0) {
		return;
	}
	
	if (initNonDinoEntities() != 0) {
		return;
	}

	if (initDinoEntity() != 0) {
		return;
	}

	if (initObstacles() != 0) {
		return;
	}

	Score::init();

	initDone = true;

	showTitleScreen();
}

Game::~Game() {
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);

	gameWindow = nullptr;
	gameRenderer = nullptr;

	SDL_Quit();
	TTF_Quit();
}

int Game::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "[Error] Game::initSDL(): SDL_Init() failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	gameWindow = SDL_CreateWindow("Dino 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gameWindow == nullptr) {
		std::cerr << "[Error] Game::initSDL(): SDL_CreateWindow() failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
	if (gameRenderer == nullptr) {
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
	
	textManager.init();
	if (textManager.getErrorCode() == -1) {
		std::cerr << errorMessage << std::endl;
		return -1;
	}

	Score::init();

	return 0;
}

void Game::showTitleScreen() {
	int time = 0;
	bool subtitleIsVisible = true;
	inLobby = true;

	while (inLobby) {
		SDL_SetRenderDrawColor(Game::gameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(Game::gameRenderer);

		textManager.drawText_Static("DINO SAUR", CENTERED, Game::SCREEN_HEIGHT / 5, 80, 150);
		if (subtitleIsVisible) {
			textManager.drawText_Static("press [SPACE] to start", CENTERED, 360, 18, 40);
		}

		SDL_RenderPresent(Game::gameRenderer);

		if (++time >= 400) {
			time = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}

		this->handleEvents();
	}
}

void Game::showGameOverScreen() {
	int time = 0;
	bool subtitleIsVisible = true;

	inLobby = true;

	int currScore = Score::getCurrentScore();

	if (currScore > Score::getHighScore()) {
		Score::setHighScore(currScore);
	}

	obstacleManager.initGameOverAnimation();

	while (inLobby) {
		SDL_SetRenderDrawColor(Game::gameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(Game::gameRenderer);

		textManager.drawText_Static_NonStatic("HIGH SCORE: ", std::to_string(Score::getHighScore()), CENTERED, 40, 24, 40);
		textManager.drawText_Static_NonStatic("CURRENT SCORE: ", std::to_string(Score::getCurrentScore()), CENTERED, 90, 24, 40);

		obstacleManager.updateGameOverAnimation();

		textManager.drawText_Static(Game::gameOverTag, CENTERED, Game::SCREEN_HEIGHT / 2 + Game::SCREEN_HEIGHT / 5, 24, Game::SCREEN_HEIGHT / 12);
		if (subtitleIsVisible) {
			textManager.drawText_Static("press [SPACE] to run again!", CENTERED, 640, 18, 40);
		}

		SDL_RenderPresent(Game::gameRenderer);

		if (++time >= 400) {
			time = 0;
			subtitleIsVisible = subtitleIsVisible ? false : true;
		}
			
		this->handleEvents();
	}
}

int Game::initNonDinoEntities() {
	try {
		map.addComponent<TransformComponent>(0, 0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT - 80);
		map.addComponent<SpriteComponent>("assets\\sprites\\BackgroundSheet.png", std::make_unique<Background>(), 0, 64, 96, 64);
		
		celestialBody.addComponent<TransformComponent>(Game::SCREEN_WIDTH, 150, 139, 130);
		celestialBody.addComponent<SpriteComponent>("assets\\sprites\\Moon.png", std::make_unique<CelestialBody>(), 0, 0, 28, 30);

		ground.addComponent<TransformComponent>(0, Game::SCREEN_HEIGHT - 80, Game::SCREEN_WIDTH, 80);
		ground.addComponent<SpriteComponent>("assets\\sprites\\GroundSheet.png", std::make_unique<Ground>(), 0, 0, 96, 16);
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
		return -1;
	}

	return 0;
}

void Game::resetNonDinoEntities() {
	TransformComponent* transformComponent = &celestialBody.getComponent<TransformComponent>();
	transformComponent->mPosition.x = Game::SCREEN_WIDTH;

	SpriteComponent* spriteComponent = &map.getComponent<SpriteComponent>();
	spriteComponent->getSprite()->setAnimation(1, 2, 500);
}

int Game::initDinoEntity() {
	try {
		dino.addComponent<TransformComponent>(60, Game::SCREEN_HEIGHT - 355, 273, 275);
		dino.addComponent<SpriteComponent>("assets\\sprites\\DinoSheet.png", std::make_unique<Dino>(), 0, 0, 32, 32);
		dino.addComponent<KeyboardController>();
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
		return -1;
	}

	return 0;
}

void Game::resetDinoEntity() {
	SpriteComponent* spriteComponent = &dino.getComponent<SpriteComponent>();

	spriteComponent->getSprite()->init();
}


int Game::initObstacles() {
	try {
		obstacleManager.init();
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
		return -1;
	}

	return 0;
}

void Game::resetObstacles() {
	obstacleManager.reset();
}

void Game::resetGame() {
	resetNonDinoEntities();
	resetDinoEntity();
	resetObstacles();

	Score::reset();

	Game::playerFail = false;
	Game::tick = 0;
}

void Game::handleEvents() {
	SDL_PollEvent(&Game::event);

	switch (event.type) {
	case SDL_QUIT:
		quit = true;
		std::cout << "Dino 2D exited..." << std::endl;
		exit(0);
	case SDL_KEYDOWN:
		if (inLobby && Game::event.key.keysym.sym == SDLK_SPACE) {
			inLobby = false;
		}
		break;
	default:
		break;
	}
}

static inline void renderClear() {
	if (SDL_RenderClear(Game::gameRenderer) < 0) {
		std::stringstream ss;
		ss << "[Error] Game::render(): SDL_RenderClear() Failed!\nDetails: " << SDL_GetError() << "\n\n";
		Game::errorMessage = ss.str();
		Game::quit = true;

		throw std::runtime_error{ Game::errorMessage };
	}
}

void Game::render() {
	renderClear();
	
	entityManager.draw();
	
	Score::draw();

	SDL_RenderPresent(Game::gameRenderer);
}

void Game::update() {
	tick++;

	obstacleManager.update();
	
	entityManager.refresh();
	entityManager.update();

	Score::update();

	Collision::checkForCollisions();
}

void Game::inGameLoop() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (!playerFail) {
		try {
			frameStart = SDL_GetTicks();
			this->handleEvents();
			this->update();
			this->render();
			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
		}
		catch (std::exception& e) {
			std::cout << e.what();
			return;
		}
	}
	
	showGameOverScreen();
	resetGame();
}