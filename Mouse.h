#ifndef MOUSE_H
#define MOUSE_H

#include "Function.h"
#include"Background.h"
class Mouse:public Background
{
public:
	SDL_Texture* tex = NULL;
	SDL_Rect rect;
	SDL_Rect point;
	Mouse();
	~Mouse();
	void SetMouse(SDL_Renderer* screen);
	void UpdateMouse();
	void RenderCopy(SDL_Renderer* screen);
	void DestroyMouse();

};
#endif
