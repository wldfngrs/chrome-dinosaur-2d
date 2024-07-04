#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#include "Game.h"

Game game;

static void gameLoopWrapper() {
	game.loop();
}

int main(int argc, char** argv) {
#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(gameLoopWrapper, 0, 1);
#else
	while (game.initializationDone() && !game.playerHasQuit()) {
		game.loop();
		SDL_Delay(16);
	}
#endif

	return 0;
}