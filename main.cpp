#include "SDL_util.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

struct Box {
	int x;
	int y;
	int size = 10;
	Box(int _x, int _y) {
		x = _x;
		y = _y;
	}
	
	void render() {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		//SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
		SDL_Rect filled_rect;
		filled_rect.x = x;
		filled_rect.y = y;
		filled_rect.w = size;
		filled_rect.h = size;
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &filled_rect);
	}

	void move() {
		x += 5;
		y += 5;
	}

	void moveLeft() {
		x -= 5;
	}

	void moveRight() {
		x += 5;
	}

	void moveDown() {
		y += 5;
	}

	void moveUp() {
		y -= 5;
	}

	bool inside(int minX, int minY, int maxX, int maxY) {
		return (minX <= x && minY <= y && x + size <= maxX && y + size <= maxY);
	}
};




int main(int argc, char* argv[])
{
	initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	Box box(10, 10);


	SDL_Event e;
	while (box.inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		box.render();
		SDL_RenderPresent(renderer);

		SDL_Delay(150);

		if (SDL_WaitEvent(&e) == 0) continue;
		if (e.type == SDL_QUIT) break;
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE: break;
			case SDLK_LEFT: 
				box.moveLeft();
				break;
			case SDLK_RIGHT:
				box.moveRight();
				break;
			case SDLK_DOWN: 
				box.moveDown();
				break;
			case SDLK_UP: 
				box.moveUp();
				break;
			default: break;
			}
		}

		box.move();

	}

	waitUntilKeyPressed();
	quitSDL(window, renderer);
	return 0;
}