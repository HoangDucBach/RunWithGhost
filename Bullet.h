#ifndef BULLET_H
#define BULLET_H

#include"Function.h"

class Bullet
{
private:
	SDL_Texture* tex = NULL;
public:
	Bullet();
	~Bullet();
	SDL_Rect rect;
	float x_float, y_float;
	void SetBullet(SDL_Renderer* screen);
	void RenderCopy(SDL_Renderer* screen);
	void DestroyBullet();
};

#endif