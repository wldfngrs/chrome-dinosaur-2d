#include "SDL.h"

#include "game.h"

#include <stdio.h>

int main(int argc, char **argv) {
	Game game;

	if (game.initError) {
		return -1;
	}

	game.mainLoop();

	return 0;
}