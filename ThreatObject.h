#pragma once
#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "Utils.h"
#include "BaseObject.h"

const int THREAT_FRAME_NUM = 12;
const int THREAT_SPEED = 6;
//const int STATE_MONEY = 4;

class ThreatObject : public BaseObject {
public:
	ThreatObject();
	~ThreatObject();

	enum walkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
		WALK_UP = 2,
		WALK_DOWN = 3,
	};


	//setter, getter position
	void setX(const int& _x) { x = _x; }
	void setY(const int& _y) { y = _y; }
	int getX() const { return x; }
	int getY() const { return y; }


	void setXVel(const int& _xVel) { x_vel_ = _xVel; }
	void setYVel(const int& _yVel) { y_vel_ = _yVel; }

	bool loadImage(std::string path, SDL_Renderer* ren);
	void setClip();
	void chooseDirection(int num);
	void moveThreat(Map& map_data, int num); //random number to turn direction
	void checkMap(Map& map_data);
	void show(SDL_Renderer* des);

private:
	int x, y; //position
	int x_vel_, y_vel_; //velocity 

	//take the frames' dimensions 
	int width_frame_;
	int height_frame_;


	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	Direction dir_type_; // left or right
	int frame_;
	int status_;
};


#endif // !THREAT_OBJECT_H_
