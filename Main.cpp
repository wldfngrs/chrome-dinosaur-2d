#include "Game.h"

int main(int argc, char** argv) {
	Game game;

	while (game.initializationDone() && !game.playerHasQuit()) {
		game.loop();
	}

	return 0;
}