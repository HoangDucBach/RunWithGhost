#ifndef SETTINGS_H
#define SETTINGS_H

#include"Function.h"
#include"AllHeader.h"
class Settings
{
private:
	SDL_Texture* tex=NULL,*texnode=NULL,*texfontvolumn=NULL;
	SDL_Rect rect, rectnode, rectfillleft,rectfillright,rectfont;
	std::string volumninfo="50";
	int volumn = 50;
public:
	Button exitbutton, speakerbutton, mutebutton;
	bool RUN = false;
	void SetSettings(SDL_Renderer* screen);
	void RenderCopy(SDL_Renderer* screen,Mouse &mouse);
	void AdjustVolumn(SDL_Renderer* screen, SDL_Event& event, Mouse& mouse, Sound& sound);
	void UpdateAll(SDL_Renderer* screen, SDL_Event& event, Mouse& mouse, Sound& sound);
};

#endif