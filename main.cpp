#include "SDL.h"

#include "game.h"

#include <stdio.h>

int main(int argc, char **argv) {
	Game game;

	if (!game.initDone) {
		return -1;
	}

	while (!game.quit) {
		game.inGameLoop();
	}

	return 0;
}