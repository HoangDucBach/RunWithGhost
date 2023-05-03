#ifndef BOSS_H
#define BOSS_H

#include"Function.h"
#include"Character.h"
#include"Bullet.h"
class Boss
{
private:
	SDL_Texture* tex = NULL,* texbossfont = NULL, * texbossredfont = NULL, * texbosstime = NULL, * texstatus = NULL;
	SDL_Rect rect,rectframe,rectbossfont,rectbossredfont,rectbosstime,rectstatus;
	SDL_Rect frame[13],framebosstime[20];
	float x_float, y_float;
	float x0, y0;
	int framecount,framebosstimecount;
	int time = 0, wait = 0;
	bool RUN = false;
public:
	void SetBoss(std::string path,SDL_Renderer* screen);
	void RenderCopy(SDL_Renderer* screen, bool& play, bool& pause);
	void BossCatch(Character& character, bool& play);
	void ResetDefault();
	void DestroyBoss();
};
class BossRambo
{
private:
	SDL_Texture* tex = NULL,*texrobot=NULL,*texbosstime=NULL,*texstatus=NULL;
	SDL_Rect rect,rectrobot,rectbosstime,rectstatus;
	SDL_Rect frame[8],framebosstime[20];
	float x_float, y_float;
	int framecount,framebosstimecount;
	int time = 0;
	int wait = 0;
	int k[10];
public:
	bool RUN = false;
	int countbullet = 0;
	void SetBossRambo(SDL_Renderer* screen);
	void AnimationBossRambo(bool& play);
	void BossShot(Character& character, std::vector<Bullet>& bullets, bool& play);
	void RenderCopy(SDL_Renderer* screen, std::vector<Bullet>& bullets, bool& play,bool &pause);
	void ResetDefault();
	void DestroyBossRambo();
};
#endif