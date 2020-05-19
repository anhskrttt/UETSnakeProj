#include "GameMap.h"

TileMap::TileMap() {}
TileMap::~TileMap() {}

GameMap::GameMap() {

}

GameMap::~GameMap() {

}

void GameMap::LoadMap(std::string path) {
	int x;
	std::ifstream file(path);
	if (file.is_open()) {
		while (!file.eof()) {
			for (int i = 0; i < MAX_MAP_Y; ++i) {
				for (int j = 0; j < MAX_MAP_X; ++j) {
					file >> x;
					game_map_.tile[i][j] = x;
				}
			}
		}
		file.close();
	}

}

void GameMap::LoadTiles(SDL_Renderer* ren) {
	tile_map[0].loadImage("resource/image/background/tile1.png", ren);
	tile_map[1].loadImage("resource/image/background/tile2.png", ren);
	tile_map[2].loadImage("resource/image/object/heart.png", ren);
	tile_map[3].loadImage("resource/image/object/coin.png", ren);

}

void GameMap::DrawMap(SDL_Renderer* ren) {
	for (int i = 0; i < MAX_MAP_Y; ++i) {
		for (int j = 0; j < MAX_MAP_X; ++j) {
			int val = game_map_.tile[i][j];
			if (val > 0) {
				tile_map[val - 1].setRect(j * TILE_SIZE, i * TILE_SIZE);
				tile_map[val - 1].render(ren, NULL);
			}

		}
	}
}

void GameMap::setMap(Map& tmp)
{
	for (int i = 0; i < MAX_MAP_Y; ++i) {
		for (int j = 0; j < MAX_MAP_X; ++j) {
			game_map_.tile[i][j] = tmp.tile[i][j];
		}
	}
}