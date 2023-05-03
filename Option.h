#ifndef OPTION_H
#define OPTION_H

#include"Function.h"
#include"Button.h"
#include"Sound.h"
class Option
{
private:
	SDL_Texture* texsetting = NULL, * texadjust = NULL, * texfontvolumn = NULL, * texblack=NULL,*texpause=NULL;
	SDL_Rect rect, rectadjust,rectfontvolumn,rectblack,rectpause;
	std::string volumninfo;
public:
	Option();
	bool show = false;
	Button setting, home, option, menu, adjustrect;
	void SetOption(SDL_Renderer* screen, int x , int y);
	void CheckActive(SDL_Event& event, bool &pause);
	void RenderCopy(SDL_Renderer* screen, Mouse& mouse,Sound &sound,const bool &play, const bool& RUN, const bool& pause);
	void AdjustVolumn(SDL_Renderer* screen, Mouse& mouse, Sound& sound);
	void DestroyOption();

};


#endif