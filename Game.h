#ifndef GAME_H
#define GAME_H

#include"AllHeader.h"
#include"Settings.h"
class Game
{
private:
	Background background,backgroundfire;
	SDL_Texture *texcount=NULL,*texinfo=NULL,*texbackground = NULL,*texpause=NULL;
	SDL_Rect rectcount,rectinfo,rectbackground,rectpause,*rectpauseframe;
	TTF_Font *fontcount=NULL;
	Complete *complete;
	Sound backgroundmusic;
	std::string countinfo;
	int countframepause = 0,fpsframepause=0;

	//Game Detail
	std::vector<Object> VectorObs;
	std::vector<Object> VectorObsMove;
	std::vector<std::string> Obstacle = { "Img/Thorn.png","Img/Ball.png" };
	bool change = false;
	//Speed 
	int SPEEDCOUNT = 0;
	int METERCOUNT = 0;
	int COUNTCOUNT = 1;
	int COUNTTIME = 1;
	//Level
	int LEVEL = 1;
	//Act check
	bool CHECK = false;
	//Size Vector
	int SizeVO = 5;
	int SizeVOM = 1;
	int SizeBlade = 0;
	//Shield
	ObjectCollect shield;
	ObjectCollect shieldred;
	//Boss Rambo
	BossRambo bossrambo;
	//Boss
	Boss boss;
	//Bullet
	std::vector<Bullet> bullets;
	//Mini
	ObjectCollect mini;
	//Fast
	ObjectCollect fast;
	//Blade
	std::vector<Blade> blades;
	//Fire Area
	Fire fire;
public:
	Button homebutton,settingbutton;
	Character *character;
	~Game();
	bool PLAY = true;
	bool RUN = false;
	bool PAUSE = false;
	int COUNT = 4;
	void SetGame(SDL_Renderer* screen, Mouse& mouse,const int &charactertype);
	void RunGame(SDL_Renderer* screen,Mouse &mouse,bool &check, const int& charactertype, Sound& sound,Settings& settings,std::string &bestscore, std::string& bestspeed);
	void CountTime(SDL_Renderer* screen);
	void ResetGame(SDL_Renderer* screen,const int & charactertype);
	void DestroyGame();
};
#endif