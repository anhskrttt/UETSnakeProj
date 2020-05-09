#include "Game.h"

Game* game = NULL;

int main(int argc, char* argv[]) {

	//reference: https://www.youtube.com/watch?v=jzasDqPmtPI&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=5
	//limit frames per second

	const int FPS = 20;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init();
	game->loadMedia();

	while (game->isRunning()) {

		game->handleEvent();
		game->update();
		game->render();

		//limit fps
		frameStart = SDL_GetTicks();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->close();

	delete game;
	game = NULL;

	return 0;
}

