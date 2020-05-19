
#include "Game.h"
#include "Utils.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "PlayerObject.h"
#include "ThreatObject.h"
#include "FoodObject.h"
#include "TextObject.h"

static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent;
static SDL_Window* gWindow = NULL;

//sub-items
BaseObject* gStartBackground = new BaseObject();
BaseObject* gBackground = new BaseObject();
BaseObject* gEndBackground = new BaseObject();

//music
Mix_Music* gBGMusic = NULL;
Mix_Music* gEndBGMusic = NULL;

Mix_Chunk* gCoinSound = NULL;
Mix_Chunk* gDeadSound = NULL;

//game-object
GameMap* game_map = NULL;
Map* map_data = NULL;
PlayerObject* player = NULL;
Strawberry* stb = NULL;
TextObject* gPoint = NULL;



//create a list of threats
std::vector<ThreatObject*> MakeThreatList() {
	std::vector<ThreatObject*> list_threat_res;

	ThreatObject* threat_obj = new ThreatObject[MAX_ENERMY];

	for (int i = 0; i < MAX_ENERMY; ++i) {
		ThreatObject* p_threat = threat_obj + i;
		if (p_threat != NULL) {
			p_threat->loadImage("resource/image/object/threat1Right.png", gRenderer);
			p_threat->setClip();
			p_threat->setX(64 + i * 5 * 64);
			p_threat->setY(64 + i * 3 * 32);

			list_threat_res.push_back(p_threat);
		}
	}
	return list_threat_res;
}

std::vector<ThreatObject*> threats_list;





Game::Game() {
	gWindow = NULL;
	gFont = NULL;

	status_ = 0;
}

Game::~Game() {

}

void Game::init() {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		running = false;
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
			running = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				running = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					running = false;
				}

				//Initialize video loading
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					running = false;
				}

				//loading font
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					running = false;
				}

			}
		}
	}

	initObj();

}


void Game::initObj() {

	//Player
	player = new PlayerObject();
	player->loadImage("resource/image/object/snakeRight.png", gRenderer);
	player->setClip();


	//Strawberry
	stb = new Strawberry();
	stb->loadImage("resource/image/object/strawberry.png", gRenderer);

	//Map-data
	map_data = new Map();
	game_map = new GameMap();
	game_map->LoadMap("resource/mapset.dat");
	*map_data = game_map->getMap();
	game_map->LoadTiles(gRenderer);

	gPoint = new TextObject();

}

void Game::loadMedia() {

	//loadBackground - const
	gStartBackground->loadImage("resource/image/background/startBackground.png", gRenderer);
	gBackground->loadImage("resource/image/background/background.png", gRenderer);
	gEndBackground->loadImage("resource/image/background/endBackground.png", gRenderer);

	//make a list of threat
	threats_list = MakeThreatList();

	//Music - const
	gBGMusic = Mix_LoadMUS("resource/audio/backgroundMusic.mp3");
	gEndBGMusic = Mix_LoadMUS("resource/audio/gameOverMusic.mp3");
	gCoinSound = Mix_LoadWAV("resource/audio/plusPointSoundEffect.wav");
	gDeadSound = Mix_LoadWAV("resource/audio/dieSoundEffect.wav");

	//load font
	gFont = TTF_OpenFont("resource/font/font.ttf", 28);

}

void Game::handleEvent() {
	while (SDL_PollEvent(&gEvent) != 0) {
		if (gEvent.type == SDL_QUIT) {
			running = false;
		}

		if (status_ == 1) {
			player->handleInputAction(gEvent); //playing
		}
		else if (status_ == 0) {
			if (gEvent.type == SDL_KEYDOWN) status_++;
		}
		else {
			if (gEvent.type == SDL_KEYDOWN && gEvent.key.keysym.sym == SDLK_r) {
				Mix_HaltMusic();
				initObj();
				status_ = 0;
			}
		}
	}
}


void Game::update() {
	if (status_ == 1) {
		if (player->isDead()) {
			Mix_HaltMusic();
			status_ = 2;

		}
		else {
			//map
			game_map->setMap(*map_data);

			//move player while checking collision with (map) and (strawberry)
			SDL_Rect tmp1 = stb->getRect();

			if (player->movePlayer(*map_data, tmp1)) {
				Mix_PlayChannel(-1, gCoinSound, 0);
				stb->changePosition(*map_data);
			}


			//update text and show point
			int tmppoint = player->getPoint();
			std::string str_val = std::to_string(tmppoint);
			//Text to Render
			std::string str_point = "Point: ";
			str_point += str_val;

			gPoint->setText(str_point);
			gPoint->loadFromRenderText(gFont, gRenderer);
		}
	}
	else if (status_ == 2) {
		if (!Mix_PlayingMusic()) {
			Mix_PlayMusic(gEndBGMusic, 0);
		}
	}


}


void Game::render() {
	SDL_RenderClear(gRenderer);

	if (status_ == 0) {
		gStartBackground->render(gRenderer);
		if (!Mix_PlayingMusic()) {
			Mix_PlayMusic(gBGMusic, -1);
		}
	}
	else if (status_ == 1) {
		//background
		gBackground->render(gRenderer);
		stb->render(gRenderer);
		game_map->DrawMap(gRenderer);

		//player
		player->show(gRenderer);

		//strawberry

		//threats
		SDL_Rect playerRect = player->getRect();
		for (int i = 0; i < threats_list.size(); ++i) {
			int r = rand() % 10 + 1;
			ThreatObject* p_threat = threats_list.at(i);
			if (p_threat != NULL) {
				if (p_threat->moveThreat(*map_data, playerRect, r)) {
					player->setDead();
					Mix_PlayChannel(-1, gDeadSound, 0);
				}

				p_threat->show(gRenderer);
			}
		}

		//text
		gPoint->renderText(gRenderer, 640, 256);
	}
	else {

		gEndBackground->render(gRenderer);
	}


	SDL_RenderPresent(gRenderer);
}

void Game::close() {

	//delete pointers used
	gBackground->free();
	gStartBackground->free();
	gEndBackground->free();

	//free object used
	player->free();
	stb->free();

	//delete pointers used
	delete map_data;
	delete game_map;
	game_map = NULL;
	map_data = NULL;



	//free the sound effects
	Mix_FreeChunk(gDeadSound);
	Mix_FreeChunk(gCoinSound);
	gDeadSound = NULL;
	gCoinSound = NULL;

	//Free the music
	Mix_FreeMusic(gBGMusic);
	Mix_FreeMusic(gEndBGMusic);
	gBGMusic = NULL;
	gEndBGMusic = NULL;

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;


	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}