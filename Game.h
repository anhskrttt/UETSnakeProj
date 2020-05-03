#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const std::string WINDOW_TITLE = "Amazed Snake";

class Game {
public:
	Game();
	~Game();

	bool init();
	void handleEvents();
	void update();
	void render();
	void close();

	bool running() { return isRunning; }

	static SDL_Renderer* gRenderer;
	static SDL_Event event;


	static SDL_Texture* gMenuTexture;
	static SDL_Texture* gInstructionTexture;
	static SDL_Texture* gBackgroundTexture;
	static SDL_Texture* gEndTexture;

	int getPoint() { return Point; }
	int Point = 0;

private:
	int cnt = 0;
	
	bool starting = true;
	bool playing = false;
	bool isRunning;
	SDL_Window* gWindow;

	
	
};

#endif // !GAME_H
