#include "game.h"

#include <sstream>

bool Game::running = false;
bool Game::initError = false;

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
		std::cerr << "initGame() Error: SDL_Init() Failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	this->window = SDL_CreateWindow("Dino 2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (this->window == nullptr) {
		std::cerr << "initGame() Error: SDL_CreateWindow() Failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (this->renderer == nullptr) {
		std::cerr << "initGame() Error: SDL_CreateRenderer() Failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	if (SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255) < 0) {
		std::cerr << "initGame() Error: SDL_SetRenderDrawColor() Failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

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
		ss << "render() Error: SDL_RenderClear() Failed!\nDetails: " << SDL_GetError() << "\n";
		this->running = false;
		throw std::runtime_error{ ss.str() };
	}

	SDL_RenderPresent(this->renderer);
}

void Game::update() {
	
}

void Game::mainLoop() {
	while (this->isRunning()) {
		try {
			this->handleEvents();
			this->update();
			this->render();
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
}