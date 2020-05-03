#include "Game.h"
#include "TextureManager.h"
#include "GameObjects.h"

Snake* snake;
Strawberry* tmpStb;

SDL_Renderer* Game::gRenderer = NULL;
SDL_Texture* Game::gMenuTexture = NULL;
SDL_Texture* Game::gBackgroundTexture = NULL;
SDL_Texture* Game::gEndTexture = NULL;

//SDL_Event Game::event;

Game::Game() {}
Game::~Game() {}

bool Game::init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				else {
					//Load media

					gMenuTexture = TextureManager::loadTexture("resource/image/menuStart.png");
					gBackgroundTexture = TextureManager::loadTexture("resource/image/background.png");
					gEndTexture = TextureManager::loadTexture("resource/image/menuEnd.png");

					snake = new Snake();
					tmpStb = new Strawberry();
				}
			}
		}
	}

	isRunning = success;

	return success;
}
void Game::handleEvents() {

	SDL_Event e;

	//SDL_PollEvent(&event);

	if (!(snake->handleEvent(e))) {
		playing = false;
	}

	switch (e.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

	if (starting) {
		if (e.type == SDL_KEYDOWN) {
			starting = false;
			playing = true;
		}
		
	}
	
	else  if (!playing) {
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_r:
				starting = true;
				snake = new Snake();
				break;

			default:
				break;
			}
		}
		
	}
	
	
}


void Game::update() {
	//static int cnt = 0;
	//cnt++;

	snake->moveSnake(tmpStb->mColliderStrawberry);

	if (snake->touch) {
		tmpStb->changePosition();
		Point++;
		printf("%d\n", Point);
		snake->touch = false;
	}
	snake->updateSnake();

	tmpStb->updateStrawberry();

	//printf("%d\n", cnt);

}
void Game::render() {
	SDL_RenderClear(gRenderer);

	
	if (starting) {
		SDL_RenderCopy(gRenderer, gMenuTexture, NULL, NULL);
		
	}
	else if (playing) {
		SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
		
		snake->renderSnake();
		tmpStb->renderStrawberry();
	}
	else {
		SDL_RenderCopy(gRenderer, gEndTexture, NULL, NULL);
	}
	

	SDL_RenderPresent(gRenderer);
}
void Game::close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gWindow = NULL;
	gRenderer = NULL;

	SDL_Quit();
}