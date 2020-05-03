#include "GameObjects.h"
#include "TextureManager.h"
#include <ctime>

//utils
bool checkCollision(SDL_Rect a, SDL_Rect b) {

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}




Snake::Snake() {
	snakeTexture = TextureManager::loadTexture("resource/image/character.png");

    xPos = 0;
    yPos = 0;

    SNAKE_STEP_X = 0;
    SNAKE_STEP_Y = 0;

    mColliderSnake.w = SNAKE_WIDTH;
    mColliderSnake.h = SNAKE_HEIGHT;
}

Snake::~Snake() {}

void Snake::renderSnake() {
    SDL_RenderCopy(Game::gRenderer, snakeTexture, NULL, &desRect);
}


void Snake::moveSnake(SDL_Rect& tmp) {
    if (!alert) {
        xPos += SNAKE_STEP_X;
        mColliderSnake.x = xPos;

        if (checkCollision(mColliderSnake, tmp)) {
            touch = true;
        }

        if ((xPos < 0) || (xPos + SNAKE_WIDTH > SCREEN_WIDTH) ) alert = true;

        if (!alert) {
        yPos += SNAKE_STEP_Y;
        mColliderSnake.y = yPos;

        if (checkCollision(mColliderSnake, tmp)) {
            touch = true;
        }

        if ((yPos < 0) || (yPos + SNAKE_HEIGHT > SCREEN_HEIGHT)) alert = true;;
        }
    }
}

void Snake::updateSnake() {

	desRect.x = xPos;
	desRect.y = yPos;
	desRect.w = 60;
	desRect.h = 60;

    
}

bool Snake::handleEvent(SDL_Event& e) {
    
    SDL_PollEvent(&e);
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: Snake::turnUp(); break;
        case SDLK_DOWN: Snake::turnDown(); break;
        case SDLK_LEFT: Snake::turnLeft(); break;
        case SDLK_RIGHT: Snake::turnRight(); break;
        }
    }

    if (alert) return false;

    return true;
}

void Snake::turnUp() {
    SNAKE_STEP_Y = -SNAKE_VEL;
    SNAKE_STEP_X = 0;
}
void Snake::turnDown() {
    SNAKE_STEP_Y = SNAKE_VEL;
    SNAKE_STEP_X = 0;
}
void Snake::turnLeft() {
    SNAKE_STEP_X = -SNAKE_VEL;
    SNAKE_STEP_Y = 0;
}
void Snake::turnRight() {
    SNAKE_STEP_X = SNAKE_VEL;
    SNAKE_STEP_Y = 0;
}




Strawberry::Strawberry() {
	strawberryTexture = TextureManager::loadTexture("resource/image/strawberry.png");

    xPos = 100;
    yPos = 100;
	
}

Strawberry::~Strawberry() {}

void Strawberry::updateStrawberry() {
	

    mColliderStrawberry.x = xPos;
    mColliderStrawberry.y = yPos;
    mColliderStrawberry.w = 15;
    mColliderStrawberry.h = 15;

	desRect.x = xPos;
	desRect.y = yPos;
	desRect.w = 15;
	desRect.h = 15;
}
void Strawberry::renderStrawberry() {
	SDL_RenderCopy(Game::gRenderer, strawberryTexture, NULL, &desRect);
}

void Strawberry::changePosition() {
    xPos = rand() % (SCREEN_WIDTH - 15);
    yPos = rand() % (SCREEN_HEIGHT - 15);

    mColliderStrawberry.x = xPos;
    mColliderStrawberry.y = yPos;
}
