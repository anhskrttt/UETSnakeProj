#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(std::string path) {
	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	SDL_Texture* res = SDL_CreateTextureFromSurface(Game::gRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return res;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect des)
{
	SDL_RenderCopy(Game::gRenderer, tex, NULL, &des);
}
