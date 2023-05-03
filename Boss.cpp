#include"Boss.h"
// Class Boss 
const int BOSS_WIDTH = 80;
const int BOSS_HEIGHT = 1040;

const int LIGHT_WIDTH = 189;
const int LIGHT_HEIGHT = 17;

const int BOSSTIME_WIDTH = 60;
const int BOSSTIME_HEIGHT = 200;


bool change_vertical = true;
bool change_horzontal = true;

bool change_horzontal_rambo = true;

bool check_boss = false;

int waitrandom = 1000;
int waitramborandom = 3000;
int fps = 1;
int fpsbossrambo = 1;
void Boss::SetBoss(std::string path,SDL_Renderer* screen)
{
	//Set Detail
	this->rect.x = 0;
	this->rect.y = 50;
	this->rect.w = BOSS_WIDTH;
	this->rect.h = BOSS_HEIGHT / 13;
	this->x_float = this->rect.x;
	this->y_float = this->rect.y;
	this->x0 = this->rect.x;
	this->y0 = this->rect.y;

	this->rectframe.x = 0;
	this->rectframe.y = 0;
	this->rectframe.w = BOSS_WIDTH;
	this->rectframe.h = BOSS_HEIGHT / 13;

	this->rectbosstime.x = 0;
	this->rectbosstime.y = 0;
	this->rectbosstime.w = BOSSTIME_WIDTH;
	this->rectbosstime.h = BOSSTIME_HEIGHT / 20;
	this->framecount = 0;

	this->rectstatus.x = 867;
	this->rectstatus.y = 83;
	this->rectstatus.w = 27;
	this->rectstatus.h = 30;

	this->x_float = this->rect.x;
	this->y_float = this->rect.y;

	this->RUN = false;
	this->time = 0;
	this->wait = 0;
	this->framebosstimecount = 0;
	//Set Global Variable
	fps = 1;
	change_vertical = true;
	change_horzontal = true;
	change_horzontal_rambo = true;
	waitrandom = 1000;
	//Set Link
	this->tex = LoadIMG(screen, path.c_str());
	this->texbosstime = LoadIMG(screen, "Img/Boss Time.png");
	this->texstatus = LoadIMG(screen, "Img/Boss Mini.png");
	//Set Frame
	for (int i = 0; i < 13; i++)
	{
		frame[i] = { rectframe.x,rectframe.y + i * BOSS_HEIGHT / 13,rectframe.w,rectframe.h };
	}
	//Set boss Time
	for (int i = 0; i < 20; i++)
	{
		framebosstime[i] = { rectbosstime.x,rectbosstime.y + i * BOSSTIME_HEIGHT / 20,rectbosstime.w,rectbosstime.h };
	}
}
void Boss::BossCatch(Character& character, bool& play)
{
	if (this->RUN)
	{
		SDL_Rect temp = character.GetRect();
		if (Distance(rect, temp) < 50)
		{
			character.killbyboss = true;
			play = false;
		}
		if (Distance(rect, temp) < 300)
		{
			character.danger = true;
			if (!character.moving && play)
			{
				float k = (temp.y - y0) / (temp.x - x0);
				if (temp.x > rect.x)
					x_float += 1;
				else if (temp.x < rect.x)
					x_float -= 1;
				y_float = k * (x_float - x0) + y0;
				rect.x = int(x_float);
				rect.y = int(y_float);
			}
			else if (play)
			{
				if (change_horzontal)
				{
					x_float += 1;
				}
				else
				{
					x_float -= 1;
				}
				if (change_vertical)
				{
					y_float -= 1;
				}
				else
				{
					y_float += 1;
				}
				if (x_float >= 1300)
				{
					change_horzontal = false;
				}
				if (x_float <= 0)
				{
					change_horzontal = true;
				}
				if (y_float <= 0)
				{
					change_vertical = false;
				}
				if (y_float >= 800)
				{
					change_vertical = true;
				}
				rect.x = int(x_float);
				rect.y = int(y_float);
				x0 = rect.x; 
				y0 = rect.y;
			}
		}
		else if (play && this->RUN)
		{
			character.danger = false;
			if (change_horzontal)
			{
				x_float += 1;
			}
			else
			{
				x_float -= 1;
			}
			if (change_vertical)
			{
				y_float -= 1;
			}
			else
			{
				y_float += 1;
			}
			if (x_float >= 1600)
			{
				change_horzontal = false;
			}
			if (x_float <= 0)
			{
				change_horzontal = true;
			}
			if (y_float <= 0)
			{
				change_vertical = false;
			}
			if (y_float >= 700)
			{
				change_vertical = true;
			}
			rect.x = int(x_float);
			rect.y = int(y_float);
			x0 = rect.x; 
			y0 = rect.y;
		}
	}
	else if (play)
	{
		character.danger = false;
	}
	rectbosstime.x = rect.x + 10;
	rectbosstime.y = rect.y - 15;
}
void Boss::RenderCopy(SDL_Renderer* screen, bool& play,bool &pause)
{
	SDL_Rect* currentframe = &frame[this->framecount];
	SDL_Rect* currentbosstimeframe = &framebosstime[this->framebosstimecount];
	//Frame
	if (framecount == 12)
	{
		this->framecount = 0;
	}
	if (fps % 3 == 0)
	{
		this->framecount++;
	}
	if (fps%waitrandom == 0)
	{
		this->RUN = true;
		check_boss = true;
	}
	if(!pause)
	fps++;
	if (this->RUN)
	{
		if(!pause)
		this->time++;
		if (this->time % 75 == 0 && this->framebosstimecount < 19 && !pause)
			this->framebosstimecount++;
		if (this->time == 1425)
		{
			this->wait = 0;
			this->time = 0;
			this->rect.x = 0;
			this->rect.y = 100;
			this->framebosstimecount = 0;
			this->x_float = this->rect.x;
			this->y_float = this->rect.y;
			this->RUN = false;
			check_boss=this->RUN;
			waitrandom = Random(1000, 2000);
			fps = 1;
		}
		SDL_RenderCopy(screen, tex, currentframe, &rect);
		SDL_RenderCopy(screen, texbosstime, currentbosstimeframe, &rectbosstime);
		SDL_RenderCopy(screen, texstatus, NULL, &rectstatus);
	}
}
void Boss::ResetDefault()
{
	//Reset Default
	this->rect.x = 0;
	this->rect.y = 100;
	this->rect.w = BOSS_WIDTH;
	this->rect.h = BOSS_HEIGHT / 13;
	this->x_float = this->rect.x;
	this->y_float = this->rect.y;
	this->x0 = this->rect.x;
	this->y0 = this->rect.y;

	this->rectframe.x = 0;
	this->rectframe.y = 0;
	this->rectframe.w = BOSS_WIDTH;
	this->rectframe.h = BOSS_HEIGHT / 13;

	this->rectbosstime.x = 0;
	this->rectbosstime.y = 0;
	this->rectbosstime.w = BOSSTIME_WIDTH;
	this->rectbosstime.h = BOSSTIME_HEIGHT / 20;
	this->framecount = 0;

	this->rectstatus.x = 867;
	this->rectstatus.y = 83;
	this->rectstatus.w = 27;
	this->rectstatus.h = 30;

	this->x_float = this->rect.x;
	this->y_float = this->rect.y;

	this->RUN = false;
	this->time = 0;
	this->wait = 0;
	this->framebosstimecount = 0;
	//Reset Global Variable
	fps = 1;
	change_vertical = true;
	change_horzontal = true;
	change_horzontal_rambo = true;
	waitrandom = 1000;
}
void Boss::DestroyBoss()
{
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(texbosstime);
	SDL_DestroyTexture(texstatus);
}
//
//
//
// Class Boss Rambo
void BossRambo::SetBossRambo(SDL_Renderer* screen)
{
	//Set Detail
	this->rectrobot.x = 0;
	this->rectrobot.y = 100;
	this->rectrobot.w = 50;
	this->rectrobot.h = 50;

	this->rectbosstime.x = 0;
	this->rectbosstime.y = 0;
	this->rectbosstime.w = BOSSTIME_WIDTH;
	this->rectbosstime.h = BOSSTIME_HEIGHT / 20;

	this->rectstatus.x = 867;
	this->rectstatus.y = 83;
	this->rectstatus.w = 30;
	this->rectstatus.h = 32;

	this->x_float = this->rectrobot.x;
	this->y_float = this->rectrobot.y;

	this->RUN = false;
	this->time = 0;
	this->wait = 0;
	this->framebosstimecount = 0;
	//Set Global Variable
	fpsbossrambo = 0;
	waitramborandom = 3000;
	//Set Link
	this->texrobot = LoadIMG(screen, "Img/Robot Shot.png");
	this->texbosstime = LoadIMG(screen, "Img/Boss Rambo Time.png");
	this->texstatus = LoadIMG(screen, "Img/Boss Rambo Mini.png");
	//Set Time Frame
	for (int i = 0; i < 20; i++)
	{
		framebosstime[i] = { rectbosstime.x,rectbosstime.y + i * BOSSTIME_HEIGHT / 20,rectbosstime.w,rectbosstime.h };
	}
}
void BossRambo::AnimationBossRambo(bool& play)
{
	if (play && RUN)
	{
		if (change_horzontal_rambo)
			x_float += 2;
		else
			x_float -= 2;
		if (rectrobot.x >= 1500)
			change_horzontal_rambo = false;
		if (rectrobot.x <= 10)
			change_horzontal_rambo = true;
		rectrobot.x =int(x_float);
		rectbosstime.x = rectrobot.x;
		rectbosstime.y = rectrobot.y - 20;
	}
}
void BossRambo::BossShot(Character& character, std::vector<Bullet>& bullets, bool& play)
{
	if(RUN)
	{
		SDL_Rect temp = character.GetRect();
		int i = 0;
		for (auto& bullet : bullets)
		{
			if (play)
			{
				if (this->RUN)
				{
					if (k[i] == 0)
					{
						bullet.y_float += 7 + i;
						bullet.rect.y = int(bullet.y_float);
					}
					else
					{
						if (bullet.rect.x < temp.x + temp.w / 2)
							bullet.rect.x -= 4;
						else
							bullet.rect.x += 4;
						bullet.y_float += 7 + i;
						bullet.rect.y = int(bullet.y_float);
					}
				}
				else
				{
					bullet.rect.x = rect.x + rectrobot.w / 2;
					bullet.rect.y = rect.y + rectrobot.y;
				}
			}
			if (bullet.rect.y >= 2000)
			{
				bullet.rect.x = rectrobot.x + rectrobot.w / 2;
				bullet.rect.y = rectrobot.y + rectrobot.h;
				bullet.y_float = bullet.rect.y;
				int j = 0;
				for (auto& bullet : bullets)
				{
					k[j] = 0;
					j++;
				}
			}
			if (Distance(temp, bullet.rect) < 10 && !character.shieldred)
			{
				play = false;
			}
			i++;
		}
		if (character.shieldred)
		{
			int j = 0;
			for (auto& bullet : bullets)
			{
				if (Distance(temp, bullet.rect) < 40)
				{
					k[j] = -5;
				}
				j++;
			}
		}
	}
}
void BossRambo::RenderCopy(SDL_Renderer* screen, std::vector<Bullet>& bullets, bool& play, bool& pause)
{
	fpsbossrambo++;
	if (fpsbossrambo % waitramborandom == 0)
		this->RUN = true;
	if (this->RUN && check_boss)
	{
		this->rectstatus.x = 30+867;
	}
	else
	{
		this->rectstatus.x = 867;
		this->rectstatus.y = 83;
	}
	if (this->RUN)
	{
		if (this->time % 75 == 0 && this->framebosstimecount < 19)
			this->framebosstimecount++;
		SDL_Rect* currentbosstimeframe = &framebosstime[framebosstimecount];
		if(!pause && play)
		{
			this->time++;
			fpsbossrambo++;
		}
		if (this->time == 1425)
		{
			this->wait = 0;
			this->time = 0;
			this->framebosstimecount = 0;
			this->RUN = false;
			waitramborandom = Random(3000, 4000);
			fpsbossrambo= 1;
		}
		for (auto& bullet : bullets)
		{
			bullet.RenderCopy(screen);
		}
		SDL_RenderCopy(screen, texbosstime, currentbosstimeframe, &rectbosstime);
		SDL_RenderCopy(screen, texrobot, NULL, &rectrobot);
		SDL_RenderCopy(screen, texstatus, NULL, &rectstatus);
	}
}
void BossRambo::ResetDefault()
{
	//Reset Default
	this->rectrobot.x = this->rect.x;
	this->rectrobot.y = this->rect.y;
	this->rectrobot.w = 50;
	this->rectrobot.h = 50;

	this->rectbosstime.x = 0;
	this->rectbosstime.y = 0;
	this->rectbosstime.w = BOSSTIME_WIDTH;
	this->rectbosstime.h = BOSSTIME_HEIGHT / 20;

	this->rectstatus.x = 867;
	this->rectstatus.y = 83;
	this->rectstatus.w = 30;
	this->rectstatus.h = 32;

	this->RUN = false;
	this->time = 0;
	this->wait = 0;
	this->framebosstimecount = 0;
	//Reset Global Variable
	fpsbossrambo = 0;
	waitramborandom = 3000;
}
void BossRambo::DestroyBossRambo()
{
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(texbosstime);
	SDL_DestroyTexture(texrobot);
	SDL_DestroyTexture(texstatus);
}