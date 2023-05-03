#ifndef TUTORIAL_H
#define TUTORIAL_H

#include"Function.h"
#include"AllHeader.h"
#include"Settings.h"
class Tutorial
{
private:
	SDL_Texture* tex, * texopenview = NULL, *texcharactertutor = NULL, * texobstacletutor = NULL, * texmagictutor = NULL, * texbosstutor = NULL, * texrobottutor = NULL,
				 * texRWG = NULL,*texfireareatutor=NULL;
	SDL_Rect rect,rectplayer,rectobstacletutor,rectmagictutor,rectbosstutor,rectrobottutor,rectRWG,rectopenview,rectfireareatutor;
	Sound backgroundmusic;
	Button *homebutton, *settingbutton,*viewbutton;
	bool up=false, down=false;
	int MOVEUP= 960,MOVEDOWN = 960;
public:
	~Tutorial();
	bool RUN = true;
	void SetTutorial(SDL_Renderer* screen);
	void MouseWheel(SDL_Event& event);
	void RenderCopy(SDL_Renderer* screen);
	void RunTutorial(SDL_Renderer* screen,SDL_Event &event,Mouse &mouse, Settings &setting,bool &check,Sound &sound);
	void UpdateCoordinate();
	void DestroyTutorial();
};

#endif