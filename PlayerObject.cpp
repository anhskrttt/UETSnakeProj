#include "PlayerObject.h"

PlayerObject::PlayerObject() {
	dead = false;
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

	point = 0;

	mCollision.x = 0;
	mCollision.y = 0;
	mCollision.y = 0;
	mCollision.y = 0;
}
PlayerObject::~PlayerObject() {

}


bool PlayerObject::loadImage(std::string path, SDL_Renderer* ren) {
	bool ret = BaseObject::loadImage(path, ren);
	if (ret) {
		width_frame_ = rect_.w;
		height_frame_ = rect_.h / 2;
	}

	mCollision.w = width_frame_;
	mCollision.h = height_frame_;
	return ret;
}

void PlayerObject::setClip()
{
	if (width_frame_ > 0 && height_frame_ > 0) {
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = 0;
		frame_clip_[1].y = height_frame_;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;
	}


}

bool PlayerObject::movePlayer(Map& map_data, SDL_Rect tmp)
{

	x += x_vel_;
	y += y_vel_;

	mCollision.x = x;
	mCollision.y = y;

	if (dir_type_.left_ == 1) {
		x_vel_ = -PLAYER_SPEED;
	}
	else if (dir_type_.right_ == 1) {
		x_vel_ = PLAYER_SPEED;
	}
	else if (dir_type_.up_ == 1) {
		y_vel_ = -PLAYER_SPEED;
	}
	else {
		y_vel_ = PLAYER_SPEED;
	}

	checkMap(map_data);

	if (checkCollision(mCollision, tmp)) {
		point += 1; //catch strawberry
		return true;
	}

	return false;

}


//Reference(Part2): https://phattrienphanmem123az.com/lap-trinh-game-c-p2/game-cpp-phan-2-ky-thuat-load-nhan-vat-game.html
void PlayerObject::checkMap(Map& map_data)
{

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
				IncreaseCoin();
			}
			else {
				if (val1 != 0 || val2 != 0) {
					map_data.tile[0][39 - blood] = 2;
					minusBlood();
					x = (x2)*TILE_SIZE;
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
				IncreaseCoin();
			}
			else {
				if (val1 != 0 || val2 != 0) {
					map_data.tile[0][39 - blood] = 2;
					minusBlood();
					x = (x2)*TILE_SIZE;
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
				IncreaseCoin();
			}
			else {
				if (val1 != 0 || val2 != 0) {
					map_data.tile[0][39 - blood] = 2;
					minusBlood();
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
				IncreaseCoin();
			}
			else {
				if (val1 != 0 || val2 != 0) {
					map_data.tile[0][39 - blood] = 2;
					minusBlood();
					y = (y2)*TILE_SIZE;
					y_vel_ = 0;
				}
			}

		}

	}

}


void PlayerObject::show(SDL_Renderer* des) {
	if (status_ == WALK_RIGHT) {
		loadImage("resource/image/object/snakeRight.png", des);
	}
	else {
		loadImage("resource/image/object/snakeLeft.png", des);
	}

	if (dir_type_.left_ == 1 || dir_type_.right_ == 1 || dir_type_.up_ == 1 || dir_type_.down_ == 1) {
		frame_++;
		if (frame_ >= 2) frame_ = 0;
	}
	else {
		frame_ = 0;
	}

	rect_.x = x;
	rect_.y = y;

	SDL_Rect* currentClip = &frame_clip_[frame_];

	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_texture_, currentClip, &renderQuad);
}

void PlayerObject::handleInputAction(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			status_ = WALK_RIGHT;
			y_vel_ = 0;
			dir_type_.right_ = 1;
			dir_type_.left_ = 0;
			dir_type_.up_ = 0;
			dir_type_.down_ = 0;
			break;
		case SDLK_LEFT:
			status_ = WALK_LEFT;
			y_vel_ = 0;
			dir_type_.right_ = 0;
			dir_type_.left_ = 1;
			dir_type_.up_ = 0;
			dir_type_.down_ = 0;
			break;
		case SDLK_UP:
			status_ = WALK_UP;
			x_vel_ = 0;
			dir_type_.right_ = 0;
			dir_type_.left_ = 0;
			dir_type_.up_ = 1;
			dir_type_.down_ = 0;
			break;
		case SDLK_DOWN:
			status_ = WALK_DOWN;
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
}

void PlayerObject::IncreaseCoin()
{
	point++;
}

void PlayerObject::minusBlood()
{
	blood--;
	if (blood < 0) {
		dead = true;
	}
}
