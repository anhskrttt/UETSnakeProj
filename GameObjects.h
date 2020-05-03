#pragma once
#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "Game.h"
//check collider


class Snake {
public:
	static const int SNAKE_WIDTH = 60;
	static const int SNAKE_HEIGHT = 60;
	static const int SNAKE_VEL = 5;
	int SNAKE_STEP_X = 0, SNAKE_STEP_Y = 0;

	Snake();
	~Snake();

	bool handleEvent(SDL_Event& e);
	void updateSnake();
	void renderSnake();
	void moveSnake(SDL_Rect& box);

	void turnUp();
	void turnDown();
	void turnLeft();
	void turnRight();

	bool touch = false;

private:
	int xPos;
	int yPos;
	int VelX, VelY;

	bool alert = false;
	

	SDL_Texture* snakeTexture;
	SDL_Rect srcRect, desRect;
	SDL_Renderer* snakeRenderer;

	SDL_Rect mColliderSnake;
};

class Strawberry {
public:
	Strawberry();
	~Strawberry();

	void updateStrawberry();
	void changePosition();
	void renderStrawberry();

	SDL_Rect mColliderStrawberry;

	

private:
	int xPos;
	int yPos;

	SDL_Texture* strawberryTexture;
	SDL_Rect srcRect, desRect;
	SDL_Renderer* strawberryRenderer;

	

};

#endif // !GAME_OBJECTS_H
