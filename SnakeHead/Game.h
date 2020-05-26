#pragma once
#ifndef GAME_H_
#define GAME_H_

#include "Utils.h"

class Game {
public:
	Game();
	~Game();

	enum STATUS {
		START = 0,
		PLAYING = 1,
		END = 2,
	};


	void init();
	void initObj();
	void loadMedia();
	void update();
	void handleEvent();
	void render();
	void close();

	bool isRunning() const { return running; }


private:
	bool running = true;
	TTF_Font* gFont;
	int status_ = 0;

};

#endif // !GAME_H_