#pragma once
#include "Game.h"

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

class TextureManager {
public:
	static SDL_Texture* loadTexture(std::string path);
	static void Draw(SDL_Texture* tex, SDL_Rect des);
};

#endif // !TEXTURE_MANAGER_H


