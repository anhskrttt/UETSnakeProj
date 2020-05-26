#include "TextObject.h"
TextObject::TextObject() {


	texture_ = NULL;
	font_ = NULL;
}

TextObject::~TextObject() {


}


bool TextObject::loadFromRenderText(TTF_Font* font, SDL_Renderer* ren) {
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		texture_ = SDL_CreateTextureFromSurface(ren, textSurface);
		if (texture_ == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return texture_ != NULL;

}

void TextObject::renderText(SDL_Renderer* des, int xpos, int ypos) {
	SDL_Rect renderQuad = { xpos,ypos,width,height };
	SDL_RenderCopy(des, texture_, NULL, &renderQuad);
}

void TextObject::free() {
	if (texture_ != NULL) {
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
	}
}