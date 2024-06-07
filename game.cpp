#include "Game.h"
#include "TransformComponent.h"
#include "KeyboardController.h"
#include "Collision.h"
#include "SpriteComponent.h"
#include "ObstacleHandler.h"
#include "Sprites.h"
#include "Font.h"
#include "HighScore.h"
#include <sstream>

SDL_Event Game::event;
bool Game::quit = false;
bool Game::playerFail = false;
std::string Game::errorMessage;
SDL_Renderer* Game::gameRenderer;

EntityManager entityManager;
Entity& map(entityManager.addEntity());
Entity& ground(entityManager.addEntity());
Entity& obstacle1 = entityManager.addEntity();
Entity& obstacle2 = entityManager.addEntity();
Entity& celestialBody = entityManager.addEntity();
Entity& Game::player = entityManager.addEntity();

Game::Game() {
	if (initSDL() != 0) {
		return;
	}

	if (initFonts() != 0) {
		return;
	}
	
	if (!showTitleScreen()) {
		return;
	}

	if (initEntities() != 0) {
		return;
	}
	
	if (initObstacles() != 0) {
		return;
	}

	initDone = true;
}

Game::~Game() {
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);

	gameWindow = nullptr;
	gameRenderer = nullptr;

	HighScore::scoreFont.reset();
	gameSubtitle.reset();
	gameTitle.reset();

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

	if (SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255) < 0) {
		std::cerr << "[Error] Game::initSDL(): SDL_SetRenderDrawColor() Failed!\nDetails: " << SDL_GetError() << "\n";
		return -1;
	}

	return 0;
}

int Game::initFonts() {
	if (TTF_Init() < 0) {
		std::cerr << "[Error] Game::initTTF(): TTF_Init() failed!\nDetails: " << TTF_GetError() << "\n";
		return -1;
	}
	
	gameTitle = std::move(std::make_unique<Font>("assets\\fonts\\Marshland_Beauty.otf", 72));

	if (gameTitle->errorCode == -1) {
		std::cerr << "[Error] Game::initTTF(): TTF_OpenFont() '" << gameTitle->pathToFont << "' failed!\nDetails: " << TTF_GetError() << "\n";
		return -1;
	}

	gameSubtitle = std::move(std::make_unique<Font>("assets\\fonts\\ALBA____.TTF", 24));
	if (gameSubtitle->errorCode == -1) {
		std::cerr << "[Error] Game::initTTF(): TTF_OpenFont() '" << gameSubtitle->pathToFont << "' failed!\nDetails: 'assets\\fonts\\ALBA____.TTF'" << TTF_GetError() << "\n";
		return -1;
	}

	HighScore::scoreFont = std::move(std::make_unique<Font>("assets\\fonts\\bunny$mambo.ttf", 24));
	if (HighScore::scoreFont->errorCode == -1) {
		std::cerr << "[Error] Game::initTTF(): TTF_OpenFont() '" << HighScore::scoreFont->pathToFont << "' failed!\nDetails: 'assets\\fonts\\bunny$mambo.ttf' " << TTF_GetError() << "\n";
		return -1;
	}

	return 0;
}

bool Game::showTitleScreen() const {
	SDL_Color titleTextColor = { 184, 37, 53 };
	SDL_Color subtitleTextColor = { 0, 0, 0 };
	gameTitle->texture = TextureManager::loadFromRenderedText("DINO RUN", gameTitle->font, titleTextColor);
	//gameSubtitle->texture = TextureManager::loadFromRenderedText("press [SPACE] to start", gameSubtitle->font, subtitleTextColor);
	
	SDL_SetRenderDrawColor(Game::gameRenderer, 0, 0, 0, 0);
	SDL_RenderClear(Game::gameRenderer);

	TextureManager::drawText(gameTitle->texture, Game::SCREEN_WIDTH / 4, Game::SCREEN_HEIGHT / 6, Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/4);
	//TextureManager::drawText(gameSubtitle->texture, Game::SCREEN_WIDTH / 4 + 10, Game::SCREEN_HEIGHT / 4 + Game::SCREEN_HEIGHT/2 + 10, 0, 0);
	
	SDL_RenderPresent(Game::gameRenderer);

	while (true) {
		try {
			this->handleEvents();
		}
		catch (std::exception& e) {
			if (quit) {
				std::cout << e.what();
				return false;
			}
	
			return true;
		}
	}
}

int Game::initEntities() {
	try {
		map.addComponent<TransformComponent>(0, 0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT - 80);
		std::unique_ptr<Background> backgroundSprite{ new Background() };
		map.addComponent<SpriteComponent>("assets\\sprites\\BackgroundSheet.png", std::move(backgroundSprite), true, 0, 64, 96, 64);

		celestialBody.addComponent<TransformComponent>(Game::SCREEN_WIDTH, 150, 139, 130);
		std::unique_ptr<CelestialBody> celestialBodySprite{ new CelestialBody() };
		celestialBody.addComponent<SpriteComponent>("assets\\sprites\\Moon.png", std::move(celestialBodySprite), false, 0, 0, 28, 30);

		ground.addComponent<TransformComponent>(0, Game::SCREEN_HEIGHT - 80, Game::SCREEN_WIDTH, 80);
		std::unique_ptr<Ground> groundSprite{ new Ground() };
		ground.addComponent<SpriteComponent>("assets\\sprites\\GroundSheet.png", std::move(groundSprite), true, 0, 0, 96, 16);

		player.addComponent<TransformComponent>(60, Game::SCREEN_HEIGHT - 355, 273, 275);
		std::unique_ptr<Dino> dinoSprite{ new Dino() };
		player.addComponent<SpriteComponent>("assets\\sprites\\DinoSheet.png", std::move(dinoSprite), true, 0, 0, 32, 32);
		player.addComponent<KeyboardController>();
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
		return -1;
	}

	return 0;
}

int Game::initObstacles() {
	try {
		ObstacleHandler::init();

		obstacle1.addComponent<TransformComponent>();
		obstacle1.addComponent<SpriteComponent>("assets\\sprites\\ObstacleSheet.png");
		ObstacleHandler::addObstacle(&obstacle1);

		obstacle2.addComponent<TransformComponent>();
		obstacle2.addComponent<SpriteComponent>("assets\\sprites\\ObstacleSheet.png");
		ObstacleHandler::addObstacle(&obstacle2);

		ObstacleHandler::loadObstacles();
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
		return -1;
	}

	return 0;
}

void Game::handleEvents() const {
	SDL_PollEvent(&Game::event);

	switch (event.type) {
	case SDL_QUIT:
		quit = true;
		throw std::exception{ "Dino 2D exited..." };
	case SDL_KEYDOWN:
		if (!initDone && Game::event.key.keysym.sym == SDLK_SPACE) {
			throw std::exception{};
		}
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

	SDL_RenderPresent(Game::gameRenderer);
}

void Game::update() {
	ObstacleHandler::fieldObstacle();
	ObstacleHandler::loadObstacles();
	
	entityManager.refresh();
	entityManager.update();

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
			break;
		}
	}
}