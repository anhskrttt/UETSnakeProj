#pragma once
#ifndef FOOD_OBJECT_H_
#define FOOD_OBJECT_H_

#include "Utils.h"
#include "BaseObject.h"

class Strawberry : public BaseObject {
public:
	Strawberry();
	~Strawberry();

	void changePosition(Map& map_data);
	bool checkMap(Map& map_data);

private:
	int x, y; //pos
};

#endif // !FOOD_OBJECT_H_
