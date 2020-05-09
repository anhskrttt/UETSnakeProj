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
BaseObject gStartBackground;
BaseObject gBackground;
BaseObject gEndBackground;

//music
Mix_Music* gBGMusic = NULL;
Mix_Music* gEndBGMusic = NULL;

Mix_Chunk* gCoinSound = NULL;
Mix_Chunk* gDeadSound = NULL;

GameMap game_map;
Map map_data;
PlayerObject player;
Strawberry stb;
TextObject gPoint;



//create a list of threats
std::vector<ThreatObject*> MakeThreatList() {
	std::vector<ThreatObject*> list_threat_res;

	ThreatObject* threat_obj = new ThreatObject[3];

	for (int i = 0; i < 2; ++i) {
		ThreatObject* p_threat = threat_obj + i;
		if (p_threat != NULL) {
			p_threat->loadImage("resource/image/object/threat1Right.png", gRenderer);
			p_threat->setClip();
			p_threat->setX(64 + i * 9 * 64);
			p_threat->setY(64 + i * 3 * 64);

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

				//loading font
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					running = false;
				}
				else {

					gFont = TTF_OpenFont("resource/image/font/font.ttf", 28);
					if (gFont == NULL) {
						running = false;
					}
				}



				//Initialize video loading
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					running = false;
				}


				

			}
		}
	}

}

void Game::loadMedia() {

	//loadBackground
	gStartBackground.loadImage("resource/image/background/startBackground.png", gRenderer);
	gBackground.loadImage("resource/image/background/background.png", gRenderer);
	gEndBackground.loadImage("resource/image/background/endBackground.png", gRenderer);

	game_map.LoadMap("mapset.dat");
	map_data = game_map.getMap();

	game_map.LoadTiles(gRenderer);

	player.loadImage("resource/image/object/snakeRight.png", gRenderer);
	player.setClip();

	threats_list = MakeThreatList();

	stb.loadImage("resource/image/object/strawberry.png", gRenderer);

	//Music
	gBGMusic = Mix_LoadMUS("resource/audio/backgroundMusic.mp3");
	gEndBGMusic = Mix_LoadMUS("resource/audio/gameOverMusic.mp3");
	gCoinSound = Mix_LoadWAV("resource/audio/plusPointSoundEffect.wav");
	gDeadSound = Mix_LoadWAV("resource/audio/dieSoundEffect.wav");
	
	
}

void Game::update() {
	if (status_ == 1) {
		if (player.isDead()) {
			Mix_HaltMusic();
			status_ = 2;

		}
		else {
			//map
			game_map.setMap(map_data);

			//move player while checking collision with (map) and (strawberry)
			SDL_Rect tmp1 = stb.getRect();

			if (player.movePlayer(map_data, tmp1)) {
				Mix_PlayChannel(-1, gCoinSound, 0);
				stb.changePosition(map_data);
			}


			//update text and show point
			int tmppoint = player.getPoint();
			std::string str_val = std::to_string(tmppoint);
			//Text to Render
			std::string str_point = "Point: ";
			str_point += str_val;

			gPoint.setText(str_point);
			gPoint.loadFromRenderText(gFont, gRenderer);
		}
	}

	
}

void Game::handleEvent() {
	while (SDL_PollEvent(&gEvent) != 0) {
		if (gEvent.type == SDL_QUIT) {
			running = false;
		}

		if (status_ == 1) {
			player.handleInputAction(gEvent, gRenderer);
		}
		else {
			if (gEvent.type == SDL_KEYDOWN) {
				status_++;
				if (status_ >= 3) {
					status_ = 0;
				}
			}
		}
	}
}

void Game::render() {
	SDL_RenderClear(gRenderer);
	
	if (status_ == 0) {
		gStartBackground.render(gRenderer);
		if (!Mix_PlayingMusic()) {
			Mix_PlayMusic(gBGMusic, -1);
		}
	}
	else if (status_ == 1) {
		//background
		gBackground.render(gRenderer);
		stb.render(gRenderer);
		game_map.DrawMap(gRenderer);

		//player
		player.show(gRenderer);

		//strawberry

		//threats
		SDL_Rect playerRect = player.getRect();
		for (int i = 0; i < threats_list.size(); ++i) {
			int r = rand() % 10 + 1;
			ThreatObject* p_threat = threats_list.at(i);
			if (p_threat != NULL) {
				if (p_threat->moveThreat(map_data, playerRect, r)) {
					Mix_PlayChannel(-1, gDeadSound, 0);
					status_ = 2;
				}

				p_threat->show(gRenderer);
			}
		}

		//text
		gPoint.renderText(gRenderer, 640, 256);
	}
	else {

		if (!Mix_PlayingMusic()) {
			Mix_PlayMusic(gEndBGMusic, 0);
		}
		Mix_ResumeMusic();
		gEndBackground.render(gRenderer);
	}


	SDL_RenderPresent(gRenderer);
}

void Game::close() {
	gBackground.free();
	gStartBackground.free();
	gEndBackground.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}