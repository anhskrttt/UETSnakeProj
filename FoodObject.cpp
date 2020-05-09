#include "FoodObject.h"

Strawberry::Strawberry() {
	x = 32*7;
	y = 32;

	rect_.x = x;
	rect_.y = y;
}

Strawberry::~Strawberry() {

}

void Strawberry::changePosition(Map& map_data) {
	srand(time(NULL));

	do {
		int i = rand() % 38 + 1;
		int j = rand() % 38 + 1;

		x = i * 32;
		y = j * 32;
	} while (checkMap(map_data));

	rect_.x = x;
	rect_.y = y;

}

bool Strawberry::checkMap(Map& map_data)
{

	int x1 = x / TILE_SIZE;
	int x2 = (x + 32 - 1) / TILE_SIZE;

	int y1 = y / TILE_SIZE;
	int y2 = (y + 32 - 1) / TILE_SIZE;


	/*
				x1y1***********x2y1
					*          *
					*          *
					*          *
					*          *
				x1y2***********x2y2



	*/

	//check horizontal and vertical


	if (map_data.tile[y1][x1] != 0 || map_data.tile[y1][x2] != 0 || map_data.tile[y2][x1] != 0 || map_data.tile[y2][x2] != 0) return true; //touch

	return false;
}