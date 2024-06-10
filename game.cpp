#include "Game.h"
#include "TransformComponent.h"
#include "KeyboardController.h"
#include "Collision.h"
#include "SpriteComponent.h"
#include "ObstacleHandler.h"
#include "Sprites.h"
#include "Font.h"
#include "Score.h"
#include <sstream>

SDL_Event Game::event;
bool Game::quit = false;
bool Game::playerFail = false;
std::string Game::errorMessage;
SDL_Renderer* Game::gameRenderer;

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
	
	if (!showTitleScreen()) {
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
}

Game::~Game() {
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);

	gameWindow = nullptr;
	gameRenderer = nullptr;

	Score::font.reset();
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

	gameSubtitle = std::move(std::make_unique<Font>("assets\\fonts\\ALBA____.TTF", 12));
	if (gameSubtitle->errorCode == -1) {
		std::cerr << "[Error] Game::initTTF(): TTF_OpenFont() '" << gameSubtitle->pathToFont << "' failed!\nDetails: 'assets\\fonts\\ALBA____.TTF'" << TTF_GetError() << "\n";
		return -1;
	}

	Score::font = std::move(std::make_unique<Font>("assets\\fonts\\bunny$mambo.ttf", 24));
	if (Score::font->errorCode == -1) {
		std::cerr << "[Error] Game::initTTF(): TTF_OpenFont() '" << Score::font->pathToFont << "' failed!\nDetails: 'assets\\fonts\\bunny$mambo.ttf' " << TTF_GetError() << "\n";
		return -1;
	}

	return 0;
}

static inline void titleSteadySubtitleBlink(SDL_Texture* titleTexture, SDL_Texture* subtitleTexture, bool subtitleIsVisible) {
	SDL_SetRenderDrawColor(Game::gameRenderer, 0, 0, 0, 0);
	SDL_RenderClear(Game::gameRenderer);
	
	TextureManager::drawText(titleTexture, Game::SCREEN_WIDTH / 4, Game::SCREEN_HEIGHT / 6, Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 4);
	if (subtitleIsVisible) {
		TextureManager::drawText(subtitleTexture, 430, 360, 420, 40);
	}
	
	SDL_RenderPresent(Game::gameRenderer);
}

bool Game::showTitleScreen() const {
	int time = 0;
	bool subtitleVisibility = true;

	SDL_Color titleTextColor = { 184, 37, 53 };
	SDL_Color subtitleTextColor = { 255, 255, 255 };
	gameTitle->texture = TextureManager::loadFromRenderedText("DINO SAUR", gameTitle->font, titleTextColor);
	gameSubtitle->texture = TextureManager::loadFromRenderedText("press [SPACE] to start", gameSubtitle->font, subtitleTextColor);

	while (true) {
		try {
			titleSteadySubtitleBlink(gameTitle->texture, gameSubtitle->texture, subtitleVisibility);
			this->handleEvents();
		}
		catch (std::exception& e) {
			if (quit) {
				std::cout << e.what();
				return false;
			}
	
			return true;
		}

		if (++time >= 400) {
			time = 0;
			subtitleVisibility = subtitleVisibility ? false : true;
		}
	}
}

int Game::initNonDinoEntities() {
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
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
		return -1;
	}

	return 0;
}

void Game::resetNonDinoEntities() {
	TransformComponent* transformComponent = &celestialBody.getComponent<TransformComponent>();
	transformComponent->position.x = Game::SCREEN_WIDTH;

	SpriteComponent* spriteComponent = &map.getComponent<SpriteComponent>();
	spriteComponent->sprite->setAnimation(1, 2, 500);
}

int Game::initDinoEntity() {
	try {
		dino.addComponent<TransformComponent>(60, Game::SCREEN_HEIGHT - 355, 273, 275);
		std::unique_ptr<Dino> dinoSprite{ new Dino() };
		dino.addComponent<SpriteComponent>("assets\\sprites\\DinoSheet.png", std::move(dinoSprite), true, 0, 0, 32, 32);
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
	
	if (spriteComponent->sprite != nullptr) {
		spriteComponent->sprite.reset();
	}
	
	spriteComponent->sprite = std::move(std::make_unique<Dino>());
	spriteComponent->init();
}


int Game::initObstacles() {
	try {
		ObstacleHandler::init();
	}
	catch (std::runtime_error& e) {
		std::cout << e.what();
		return -1;
	}

	return 0;
}

void Game::resetObstacles() {
	ObstacleHandler::reset();
}

void Game::resetGame() {
	resetNonDinoEntities();
	resetDinoEntity();
	resetObstacles();

	Score::reset();

	Game::playerFail = false;
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
	tick++;

	ObstacleHandler::update();
	
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

	resetGame();
}