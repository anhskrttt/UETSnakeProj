#include "Game.h"

Game* game = NULL;

int main(int argc, char* argv[]) {

	//reference: https://www.youtube.com/watch?v=jzasDqPmtPI&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=
	//reference2: https://phattrienphanmem123az.com/lap-trinh-game-c-p2
	//limit frames per second

	const int FPS = 20;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init();
	game->loadMedia();

	while (game->isRunning()) {
		frameStart = SDL_GetTicks();

		game->handleEvent();
		game->update();
		game->render();

		//limit fps
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
