#pragma once
#ifndef MAP_GAME_H_
#define MAP_GAME_H_

#include "Utils.h"
#include "BaseObject.h"


const int MAX_TILES = 4;

class TileMap : public BaseObject {
public:
	TileMap();
	~TileMap();
};

class GameMap {
public:
	GameMap();
	~GameMap();

	void LoadMap(std::string path);
	void LoadTiles(SDL_Renderer* ren);
	void DrawMap(SDL_Renderer* ren);

	Map getMap() const { return game_map_; }
	void setMap(Map& tmp);

private:
	Map game_map_;
	TileMap tile_map[MAX_TILES];
};

#endif // !MAP_GAME_H_
