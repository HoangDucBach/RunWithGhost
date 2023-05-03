#ifndef FIRE_H
#define FIRE_H

#include"AllHeader.h"
#include"Function.h"

class Fire
{
private:
	SDL_Texture* tex;
	SDL_Rect rect;
	float x_float, y_float, w_float, h_float;
	float r;
	int fps = 0;
	int time = 300;
public:
	bool RUN = false;
	void SetFire(SDL_Renderer* screen);
	void RenderCopy(SDL_Renderer* screen);
	void CheckDanger(Character &character,bool &play);
	void Minimum();
	void ResetDefault();
};
#endif