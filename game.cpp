#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

#include <sstream>

std::string Game::errorMessage;

EntityManager entityManager;

bool Game::running = false;
bool Game::initError = false;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& map(entityManager.addEntity());
auto& ground(entityManager.addEntity());
auto& dino(entityManager.addEntity());

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupObstacles,
	groupColliders
};

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

	//(this->dinoHandler).setObjectHandler(new GameObject("assets\\Classic\\day_dino.png", this->renderer, 0, 0));

	map.addComponent<TransformComponent>(0, 0, 480, 900, 1);
	map.addComponent<BackgroundComponent>("assets\\lvl1\\background.png", true);
	map.addComponent<CelestialComponent>("assets\\lvl1\\moon.png");
	
	ground.addComponent<TransformComponent>(0, 400, 80, 900, 1);
	ground.addComponent<GroundComponent>("assets\\lvl1\\ground.png", 3, 150);
	ground.addComponent<ColliderComponent>("ground");

	dino.addComponent<TransformComponent>(60, 225, 175, 173, 1);
	dino.addComponent<DinoComponent>("assets\\lvl1\\DinoSheet.png", true);
	dino.addComponent<KeyboardController>();
	dino.addComponent<ColliderComponent>("dino");


	Game::running = true;

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
	
	entityManager.draw();
	if (!Game::running) throw std::runtime_error{ Game::errorMessage };

	SDL_RenderPresent(this->renderer);
}

void Game::update() {
	entityManager.refresh();
	entityManager.update();

	for (auto cc : colliders) {
		//Collision::AABB(dino.getComponent<ColliderComponent>(), *cc);
	}
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