#pragma once
#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "Utils.h"

class TextObject {
public:
	TextObject();
	~TextObject();

	bool loadFromFile(std::string path);
	bool loadFromRenderText(TTF_Font* font, SDL_Renderer* ren);
	void free();


	void renderText(SDL_Renderer* des, int xpos, int ypos);

	int getWidth() { return width; }
	int getHight() { return height; }

	void setText(const std::string& text) { str_val_ = text; }
	std::string getText() const { return str_val_; }

private:
	std::string str_val_;
	TTF_Font* font_;
	SDL_Color text_color_ = { 255,255,255 };
	SDL_Texture* texture_;

	int width, height;
};

#endif // !TEXT_OBJECT_H_
