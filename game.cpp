#include "Game.h"
#include "TransformComponent.h"
#include "KeyboardController.h"
#include "Collision.h"
#include "SpriteComponent.h"
#include "ObstacleHandler.h"
#include "Sprites.h"
#include <sstream>

std::string Game::errorMessage;

bool Game::running = false;
bool Game::initError = false;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

EntityManager Game::entityManager;

Entity& map(Game::entityManager.addEntity());
Entity& celestialBody(Game::entityManager.addEntity());
Entity& ground(Game::entityManager.addEntity());
Entity& Game::player = Game::entityManager.addEntity();

Entity& obstacle1 = Game::entityManager.addEntity();
Entity& obstacle2 = Game::entityManager.addEntity();

ObstacleHandler Game::obstacleHandler;

int Game::tick = 0;

Game::Game() {
	if (this->initGame() != 0) {
		this->initError = true;
	}
}

Game::~Game() {
	this->closeGame();
}

int Game::initGame() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "[Error] Game::initGame(): SDL_Init() Failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	this->window = SDL_CreateWindow("Dino 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (this->window == nullptr) {
		std::cerr << "[Error] Game::initGame(): SDL_CreateWindow() Failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (this->renderer == nullptr) {
		std::cerr << "[Error] Game::initGame(): SDL_CreateRenderer() Failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	if (SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255) < 0) {
		std::cerr << "[Error] Game::initGame(): SDL_SetRenderDrawColor() Failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	map.addComponent<TransformComponent>(0, 0, Game::SCREEN_WIDTH, 400, 1);
	std::unique_ptr<Background> backgroundSprite{ new Background() };
	map.addComponent<SpriteComponent>("assets\\BackgroundSheet.png", std::move(backgroundSprite), true, 0, 64, 96, 64);

	celestialBody.addComponent<TransformComponent>(Game::SCREEN_WIDTH, 100, 80, 72, 1);
	std::unique_ptr<CelestialBody> celestialBodySprite{ new CelestialBody() };
	celestialBody.addComponent<SpriteComponent>("assets\\Moon.png", std::move(celestialBodySprite), false, 0, 0, 28, 30);
	
	ground.addComponent<TransformComponent>(0, 400, Game::SCREEN_WIDTH, 80, 1);
	std::unique_ptr<Ground> groundSprite{ new Ground() };
	ground.addComponent<SpriteComponent>("assets\\GroundSheet.png", std::move(groundSprite), true, 0, 0, 96, 16);

	player.addComponent<TransformComponent>(60, 225, 173, 175, 1);
	std::unique_ptr<Dino> dinoSprite{ new Dino() };
	player.addComponent<SpriteComponent>("assets\\DinoSheet.png", std::move(dinoSprite), true, 0, 0, 32, 32);
	player.addComponent<KeyboardController>();


	/*Skeletal base entities, the components will be properly set in the loadObstacles function*/
	Game::obstacleHandler.init();
	obstacle1.addComponent<TransformComponent>();
	obstacle1.addComponent<SpriteComponent>("assets\\ObstacleSheet.png");
	Game::obstacleHandler.addObstacle(&obstacle1);
	obstacle2.addComponent<TransformComponent>();
	obstacle2.addComponent<SpriteComponent>("assets\\ObstacleSheet.png");
	Game::obstacleHandler.addObstacle(&obstacle2);

	Game::running = true;

	Game::obstacleHandler.loadObstacles();

	return 0;
}

void Game::handleEvents() {
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		this->closeGame();
	default:
		break;
	}
}

int Game::getTick() const {
	return tick;
}

static inline void GameRender() {
	if (SDL_RenderClear(Game::renderer) < 0) {
		std::stringstream ss;
		ss << "[ERROR] Game::render(): SDL_RenderClear() Failed!\nDetails: " << SDL_GetError() << "\n\n";
		Game::errorMessage = ss.str();
		Game::running = false;
	}
}

void Game::render() {
	GameRender();
	if (!Game::running) throw std::runtime_error{ Game::errorMessage };
	
	Game::entityManager.draw();
	if (!Game::running) throw std::runtime_error{ Game::errorMessage };

	SDL_RenderPresent(this->renderer);
}

void Game::update() {
	Game::obstacleHandler.fieldObstacle();
	Game::obstacleHandler.loadObstacles();
	
	Game::entityManager.refresh();
	Game::entityManager.update();

	Collision::checkForCollisions();
}

void Game::mainLoop() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (Game::running) {
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
		catch (std::runtime_error& e) {
			std::cout << e.what();
		}
	}
}

void Game::closeGame() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	
	this->window = nullptr;
	this->renderer = nullptr;

	SDL_Quit();

	std::cout << "Dino 2D exited...\n";
	exit(0);
}