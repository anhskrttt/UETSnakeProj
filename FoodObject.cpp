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
	int i, j; //a point
	do {
		i = rand() % 37 + 1;
		j = rand() % 17 + 1;


	} while (map_data.tile[j][i] != 0); //make sure the strawberry wont render inside the border

	x = i * 32;
	y = j * 32;
	rect_.x = x;
	rect_.y = y;
}
