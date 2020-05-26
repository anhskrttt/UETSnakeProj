#pragma once
#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "Utils.h"
#include "BaseObject.h"

const int PLAYER_SPEED = 8;
const int PLAYER_MAX_BLOOD = 3;

//Snake
class PlayerObject : public BaseObject {
public:
	PlayerObject();
	~PlayerObject();

	enum walkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN = 3,
	};

	bool loadImage(std::string path, SDL_Renderer* ren);
	void setClip();
	bool movePlayer(Map& map_data, SDL_Rect tmp);
	void checkMap(Map& map_data);
	void show(SDL_Renderer* des);
	void handleInputAction(SDL_Event e);

	void IncreaseCoin();
	void minusBlood();
	int getPoint() const { return point; }
	int getBlood() const { return blood; }
	void plusPoint(int& _p) { point += _p; }

	bool isDead() const { return dead; }
	void setDead() { dead = true; }
	SDL_Rect getRect() const { return mCollision; } //return to check collision

private:
	int x, y; //position
	int x_vel_, y_vel_; //velocity 

	//take the frames' dimensions 
	int width_frame_;
	int height_frame_;

	//coin, blood
	int point = 0;
	int blood = PLAYER_MAX_BLOOD;
	bool dead;

	SDL_Rect frame_clip_[2];
	Direction dir_type_; // left or right
	int frame_;
	int status_;

	SDL_Rect mCollision;
};


#endif // !PLAYER_OBJECT_H_