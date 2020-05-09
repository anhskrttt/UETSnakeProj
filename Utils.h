#pragma once
#ifndef UTILS_H_
#define UTILS_H_


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>


const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const std::string WINDOW_TITLE = "Snake";

const int TILE_SIZE = 32;
const int MAX_MAP_X = 40;
const int MAX_MAP_Y = 20;
const int STATE_MONEY = 4;

static SDL_Renderer* gRenderer = NULL;
static SDL_Window* gWindow= NULL;
static SDL_Event gEvent;


struct Map {
	int tile[MAX_MAP_Y][MAX_MAP_X];
	
	std::string file_name_;
};

struct Direction {
	int left_;
	int right_;
	int up_;
	int down_;
};

bool checkCollision(SDL_Rect a, SDL_Rect b);

#endif // !UTILS_H_