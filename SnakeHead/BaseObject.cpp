#include "BaseObject.h"

BaseObject::BaseObject() {
	p_texture_ = NULL;
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
}

BaseObject::~BaseObject() {
	free();
}

bool BaseObject::loadImage(std::string path, SDL_Renderer* ren) {
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			rect_.w = loadedSurface->w;
			rect_.h = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	p_texture_ = newTexture;

	return p_texture_ != NULL;
}

void BaseObject::render(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h };
	SDL_RenderCopy(des, p_texture_, clip, &renderQuad);
}

void BaseObject::free()
{
	//Free texture if it exists
	if (p_texture_ != NULL)
	{
		SDL_DestroyTexture(p_texture_);
		p_texture_ = NULL;
		rect_.w = 0;
		rect_.h = 0;
	}
}