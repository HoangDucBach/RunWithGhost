#ifndef COMPLETE_H
#define COMPLETE_H

#include"Function.h"
#include"Widgets.h"
#include"Character.h"
class Complete
{
private:
	SDL_Texture* tex = NULL, * texfontmeter = NULL, * texfontspeed = NULL;
	SDL_Rect rect,rectfontmeter,rectfontspeed,rectadjust,rectfontvolumn;
	TTF_Font *font=NULL;
	std::string meterinfo;
	std::string speedinfo;
public:
	Button again;
	bool show = false;
	Sound gameoversound;
	void RenderCopy(SDL_Renderer* screen, Mouse& mouse,const std::string& bestscore);
	void SetComplete(SDL_Renderer* screen);
	void UpdateComplete(SDL_Renderer* screen, Character& character,int & metercount, Sound& sound);
	void CheckActive(SDL_Event& event);
	void DestroyComplete();
};
#endif