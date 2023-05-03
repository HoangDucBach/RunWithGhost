#ifndef BUTTON_H
#define BUTTON_H
#include"Function.h"
#include"Mouse.h"
class Button
{
public:
	SDL_Texture* tex=NULL,*texreplace=NULL;
	SDL_Rect rect,rectreplace;
	bool IsSelected = false;
	bool IsPoint = false;
	void SetButton(std::string path1, std::string path2, SDL_Renderer* screen,const SDL_Rect& rect_, const SDL_Rect& rectreplace_);
	void UpdateButton(Mouse &mouse);
	void RenderCopy(SDL_Renderer* screen);
	void CheckActive(SDL_Event& event);
	void DestroyButton();
};

#endif 

