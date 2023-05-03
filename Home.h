#ifndef HOME_H
#define HOME_H

#include"Function.h"
#include"Game.h"
#include"Tutorial.h"
class Home
{
private:
	Background background;
	Button play;
	Game *game;
	Mouse mouse;
	Button exitbutton,settingsbutton,tutorialbutton;
	Button buttonselect[3];
	SDL_Rect rectcsf[3][24], rectcs[3];
	SDL_Rect rectrwg, rectcurrent, rectbestscore, rectbestspeed;
	SDL_Rect framerwg[44], rectcharacterlist[3];
	SDL_Rect* currentframecs[3];
	SDL_Texture* texrwg=NULL,*texcharacter[3], * texcurrent = NULL,*texbestscore=NULL,*texbestspeed=NULL;
	SDL_Texture** texcs;
	Settings settings;
	Sound backgroundmusic;
	Tutorial *tutorial;
	int framerwgcount ;
	int currentcharacter=0;
	int framecountcs[3] = { 0 };
	std::string BESTSCORE ;
	std::string BESTSPEED ;
	bool RUN = true;
public:
	Home();
	void SetHome(SDL_Renderer* screen);
	void CharacterSelectRenderCopy(SDL_Renderer* screen);
	void RenderCopy(SDL_Renderer* screen, SDL_Event& event, SDL_Window* window);
	void DestroyHome(SDL_Renderer* screen);
	void UpdateAll(SDL_Renderer* screen);
};

#endif