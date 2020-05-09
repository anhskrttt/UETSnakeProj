#include "Utils.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "PlayerObject.h"
#include "ThreatObject.h"
#include "FoodObject.h"
#include "TextObject.h"

BaseObject gBackground;
GameMap game_map;
PlayerObject player;
Strawberry stb;

TTF_Font* gFont = NULL;



bool init() {

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

				//loading font
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
				else {
					
					gFont = TTF_OpenFont("resource/image/font.ttf", 28);
					if (gFont == NULL) {
						success = false;
					}
				}

				//Initialize video loading
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void close() {
	gBackground.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::vector<ThreatObject*> MakeThreatList() {
	std::vector<ThreatObject*> list_threat_res;

	ThreatObject* threat_obj = new ThreatObject[3];

	for (int i = 0; i < 2; ++i) {
		ThreatObject* p_threat = threat_obj + i;
		if (p_threat != NULL) {
			p_threat->loadImage("resource/image/object/threat1Right.png", gRenderer);
			p_threat->setClip();
			p_threat->setX(64+i*9*64);
			p_threat->setY(64+i*3*64);

			list_threat_res.push_back(p_threat);
		}
	}
	return list_threat_res;

}

bool loadBackground() {
	bool ret = gBackground.loadImage("resource/image/background/background.png", gRenderer);
	if (ret) return true;
	return false;
}

int main(int argc, char* argv[]) {
	if (!init()) {
		return -1;
	}
	else {
		if (!loadBackground()) {
			return -1;
		}
		else {
			srand(0);
			//reference: https://www.youtube.com/watch?v=jzasDqPmtPI&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=5
			//limit frames per second

			const int FPS = 10;
			const int frameDelay = 1000 / FPS;

			Uint32 frameStart;
			int frameTime;

			game_map.LoadMap("mapset.dat");
			Map map_data = game_map.getMap();
			game_map.LoadTiles(gRenderer);
			player.loadImage("resource/image/object/snakeRight.png", gRenderer);
			player.setClip();

			stb.loadImage("resource/image/object/strawberry.png", gRenderer);

			std::vector<ThreatObject*> threats_list = MakeThreatList();

			//Text
			TextObject gPoint;

			bool quit = false;
			while (!quit) {
				frameStart = SDL_GetTicks();

				frameTime = SDL_GetTicks() - frameStart;

				if (frameDelay > frameTime) {
					SDL_Delay(frameDelay - frameTime);
				}

				while (SDL_PollEvent(&gEvent) != 0) {
					if (gEvent.type == SDL_QUIT) {
						quit = true;
					}

					player.handleInputAction(gEvent, gRenderer);
				}

				SDL_RenderClear(gRenderer);

				gBackground.render(gRenderer, NULL);

				game_map.setMap(map_data);

				game_map.DrawMap(gRenderer);

				int r = rand() % 6 + 1;
				for (int i = 0; i < threats_list.size(); ++i) {
					int r = rand() % 8 + 1;
					ThreatObject* p_threat = threats_list.at(i);
					if (p_threat != NULL) {
						p_threat->moveThreat(map_data, r);
						p_threat->show(gRenderer);
					}
				}

				player.show(gRenderer);
				stb.render(gRenderer);

				
				SDL_Rect tmp1 = stb.getRect();
				//SDL_Rect tmp2 = player.getRect();

				if (player.movePlayer(map_data, tmp1)) {
					stb.changePosition(map_data);
				}

				//player.movePlayer(map_data, tmp1);

				//show point
				std::string str_point = "Point: ";
				int tmppoint = player.getPoint();
				std::string str_val = std::to_string(tmppoint);
				str_point += str_val;

				gPoint.setText(str_point);
				gPoint.loadFromRenderText(gFont, gRenderer);
				gPoint.renderText(gRenderer, 640, 256);
				

				SDL_RenderPresent(gRenderer);

				
			}
		}
	}

	close();
	return 0;
}