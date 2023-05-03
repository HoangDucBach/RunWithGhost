#ifndef CHARACTER_H
#define CHARACTER_H

#include"Function.h"
class Character
{
private:
	SDL_Texture* tex = NULL, * texbreak = NULL, * texdead = NULL,*texdanger=NULL,*texsurfing=NULL,*texshield=NULL,*texshieldtime=NULL
				,*texshieldred=NULL,*texshieldredtime=NULL;
	SDL_Texture *texfontspeed = NULL,*texfontmeter=NULL,*texfontmetercount=NULL;
	SDL_Rect rect,rectbreakframe, rectdeadframe,rectdanger,rectsurfingframe;
	SDL_Rect rectfontmeter,rectfontspeed,rectfontmetercount,rectshield,rectshieldtime,rectshieldredtime;
	TTF_Font* font = NULL;
	SDL_Rect frame[3], framebreak[5], framedead[10],frameshieldtime[10],frameshieldredtime[10];
	float x_float, y_float;
	int framewidth,frameheight;
	int framebreakcount,framedeadcount,frameshieldtimecount,frameshieldredtimecount;
	int timemini = 0;
	int timefast = 300;
	int speedcurrent;
	std::string speedinfo;
	std::string meterinfo;
	std::string metercountinfo;
	std::string speedcountinfo;
public:
	float aright, aleft; //acceleration
	int speed, meter;
	bool right, left, brake;
	bool moving = false;
	bool killbyboss = false;
	bool danger = false;
	bool shield = false,shieldred=false;
	bool mini = false,fast=false;
	bool burn = false;
	SDL_Rect GetRect();
	void SetCharacter(std::string path, SDL_Renderer* screen, const int& charactertype);
	void ControlCharacter(SDL_Event& event,int &SPEED,SDL_Renderer* screen, const bool& play, const bool& pause);
	void RenderCopy(SDL_Renderer* screen,bool& play);
	void UpdateInfo(SDL_Renderer* screen, int &metercount, int& speedcount, bool& play);
	void ResetDefault();
	void DestroyCharacter();
};

#endif