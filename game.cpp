#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

#include <sstream>

GameObject* dino;

bool Game::running = false;
bool Game::initError = false;

SDL_Renderer* Game::renderer = nullptr;

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

	dino = new GameObject("assets\\Classic\\day_dino.png", 0, 0);

	this->running = true;

	return 0;
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		this->running = false;
		break;
	default:
		break;
	}
}

void Game::render() {
	std::stringstream ss;
	if (SDL_RenderClear(this->renderer) < 0) {
		ss << "[ERROR] Game::render(): SDL_RenderClear() Failed!\n[Details] " << SDL_GetError() << "\n";
		this->running = false;
		throw std::runtime_error{ ss.str() };
	}

	if (dino->render() < 0) {
		ss << "[ERROR] " << dino->getErrorMessage() << " Game::render(): SDL_RenderCopy() Failed!\nDetails: " << SDL_GetError() << "\n";
		this->running = false;
		throw std::runtime_error{ ss.str() };
	}

	SDL_RenderPresent(this->renderer);
}

void Game::update() {
	dino->update();
}

void Game::mainLoop() {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	while (this->isRunning()) {
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

std::string Game::getErrorMessage() {
	return this->errorMessage;
}

void Game::closeGame() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	
	this->window = nullptr;
	this->renderer = nullptr;

	SDL_Quit();

	std::cout << "Dino 2D exited...\n";
}