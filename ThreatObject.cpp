#include "ThreatObject.h"

ThreatObject::ThreatObject() {
	frame_ = 0;

	x = 64 * 6;
	y = 64;

	x_vel_ = 0;
	y_vel_ = 0;

	width_frame_ = 0;
	height_frame_ = 0;

	status_ = 0;
	dir_type_.left_ = 0;
	dir_type_.right_ = 0;
	dir_type_.up_ = 0;
	dir_type_.down_ = 0;

	mCollision.x = 0;
	mCollision.y = 0;
	mCollision.w = 32;
	mCollision.h = 32;

}
ThreatObject::~ThreatObject() {}


bool ThreatObject::loadImage(std::string path, SDL_Renderer* ren) {
	bool ret = BaseObject::loadImage(path, ren);
	if (ret) {
		width_frame_ = rect_.w / 12;
		height_frame_ = rect_.h;
	}
	return ret;
}

void ThreatObject::setClip() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2 * width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3 * width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4 * width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5 * width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 6 * width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = 7 * width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;

		frame_clip_[8].x = 8 * width_frame_;
		frame_clip_[8].y = 0;
		frame_clip_[8].w = width_frame_;
		frame_clip_[8].h = height_frame_;

		frame_clip_[9].x = 9 * width_frame_;
		frame_clip_[9].y = 0;
		frame_clip_[9].w = width_frame_;
		frame_clip_[9].h = height_frame_;

		frame_clip_[10].x = 10 * width_frame_;
		frame_clip_[10].y = 0;
		frame_clip_[10].w = width_frame_;
		frame_clip_[10].h = height_frame_;

		frame_clip_[11].x = 11 * width_frame_;
		frame_clip_[11].y = 0;
		frame_clip_[11].w = width_frame_;
		frame_clip_[11].h = height_frame_;
	}
}
void ThreatObject::chooseDirection(int num)
{
	switch (num)
	{
	case 1:
		status_ = WALK_RIGHT;
		//x_vel_ = PLAYER_SPEED;
		y_vel_ = 0;
		dir_type_.right_ = 1;
		dir_type_.left_ = 0;
		dir_type_.up_ = 0;
		dir_type_.down_ = 0;
		break;
	case 2:
		status_ = WALK_LEFT;
		//x_vel_ = -PLAYER_SPEED;
		y_vel_ = 0;
		dir_type_.right_ = 0;
		dir_type_.left_ = 1;
		dir_type_.up_ = 0;
		dir_type_.down_ = 0;
		break;
	case 3:
		status_ = WALK_UP;
		//y_vel_ = -PLAYER_SPEED;
		x_vel_ = 0;
		dir_type_.right_ = 0;
		dir_type_.left_ = 0;
		dir_type_.up_ = 1;
		dir_type_.down_ = 0;
		break;
	case 4:
		status_ = WALK_DOWN;
		//y_vel_ = PLAYER_SPEED;
		x_vel_ = 0;
		dir_type_.right_ = 0;
		dir_type_.left_ = 0;
		dir_type_.up_ = 0;
		dir_type_.down_ = 1;
		break;
	default:
		break;
	}

}

bool ThreatObject::moveThreat(Map& map_data, SDL_Rect tmp, int num) {
	chooseDirection(num);
	x += x_vel_;
	y += y_vel_;

	mCollision.x = x;
	mCollision.y = y;

	if (dir_type_.left_ == 1) {
		x_vel_ = -THREAT_SPEED;
	}
	else if (dir_type_.right_ == 1) {
		x_vel_ = THREAT_SPEED;
	}
	else if (dir_type_.up_ == 1) {
		y_vel_ = -THREAT_SPEED;
	}
	else {
		y_vel_ = THREAT_SPEED;
	}

	checkMap(map_data);

	return checkCollision(tmp, mCollision);
}
void ThreatObject::checkMap(Map& map_data) {
	int x1 = x / TILE_SIZE;
	int x2 = (x + width_frame_ - 1) / TILE_SIZE;

	int y1 = y / TILE_SIZE;
	int y2 = (y + height_frame_ - 1) / TILE_SIZE;


	/*
				x1y1***********x2y1
					*          *
					*          *
					*          *
					*          *
				x1y2***********x2y2
	*/

	//check horizontal and vertical

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		int val1, val2;

		if (x_vel_ > 0) {
			val1 = map_data.tile[y1][x2];
			val2 = map_data.tile[y2][x2];


			if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else {
				if (val1 != 0 || val2 != 0) {
					x = x2 * TILE_SIZE;
					x -= width_frame_;
					x_vel_ = 0;
				}
			}

		}
		else if (x_vel_ < 0) {
			val1 = map_data.tile[y1][x1];
			val2 = map_data.tile[y2][x1];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
			}
			else {
				if (val1 != 0 || val2 != 0) {
					x = x2 * TILE_SIZE;
					x_vel_ = 0;
				}
			}
		}

		if (y_vel_ > 0) {
			val1 = map_data.tile[y2][x1];
			val2 = map_data.tile[y2][x2];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else {
				if (val1 != 0 || val2 != 0) {
					y = (y2)*TILE_SIZE;
					y -= height_frame_;
					y_vel_ = 0;
				}
			}
		}
		else if (y_vel_ < 0) {

			val1 = map_data.tile[y1][x1];
			val2 = map_data.tile[y1][x2];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
			}
			else {
				if (val1 != 0 || val2 != 0) {
					y = y2 * TILE_SIZE;
					y_vel_ = 0;
				}
			}

		}

		if (x < 32) x = 32;
		else if (x > SCREEN_WIDTH - 64) x = SCREEN_WIDTH - 64;

		if (y < 32) y = 32;
		else if (y > SCREEN_HEIGHT - 64) y = SCREEN_HEIGHT - 64;

	}
}

void ThreatObject::show(SDL_Renderer* des) {
	if (status_ == WALK_RIGHT) {
		loadImage("resource/image/object/threat1Right.png", des);
	}
	else {
		loadImage("resource/image/object/threat1Left.png", des);
	}

	frame_++;
	if (frame_ >= THREAT_FRAME_NUM) frame_ = 0;


	rect_.x = x;
	rect_.y = y;

	SDL_Rect* currentClip = &frame_clip_[frame_];

	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_texture_, currentClip, &renderQuad);
}