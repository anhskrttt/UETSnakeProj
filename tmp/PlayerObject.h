#pragma once
#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "Utils.h"
#include "BaseObject.h"

const int PLAYER_SPEED = 8;
//const int STATE_MONEY = 4;
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
	void handleInputAction(SDL_Event e, SDL_Renderer* ren);

	void IncreaseCoin();
	int getPoint() { return cntcoin; }
	
	//void LoadMap(std::string path);
private:
	int x, y; //position
	int x_vel_, y_vel_; //velocity 

	//take the frames' dimensions 
	int width_frame_;
	int height_frame_;

	//coin, blood
	int cntcoin;

	SDL_Rect frame_clip_[2];
	Direction dir_type_; // left or right
	int frame_;
	int status_;
	SDL_Rect mCollision;
};


#endif // !PLAYER_OBJECT_H_
