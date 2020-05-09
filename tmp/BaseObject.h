#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Utils.h"


class BaseObject {
public:
	BaseObject();
	~BaseObject();

	void setRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
	SDL_Rect getRect() { return rect_; }
	SDL_Texture* getObject() { return p_texture_; }

	virtual bool loadImage(std::string path, SDL_Renderer* ren);
	void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void free();
protected:
	SDL_Rect rect_; // loading full image, optional destination and size -> this is the clip
	SDL_Texture* p_texture_;
};

#endif // !BASE_OBJECT_H_
