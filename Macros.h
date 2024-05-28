#pragma once

#define PRESS_DOWN_ARROW	((Game::event.type == SDL_KEYDOWN) && (Game::event.key.keysym.sym == SDLK_DOWN))
#define RELEASE_DOWN_ARROW	((Game::event.type == SDL_KEYUP) && (Game::event.key.keysym.sym == SDLK_DOWN))
#define PRESS_SPACE			((Game::event.type == SDL_KEYDOWN) && (Game::event.key.keysym.sym == SDLK_SPACE))
#define PRESS_UP_ARROW		((Game::event.type == SDL_KEYUP) && (Game::event.key.keysym.sym == SDLK_UP))