#include"Character.h"
const int CHARACTER_WIDTH = 30;
const int CHARACTER_HEIGHT = 90;

const int CHARACTERBREAK_WIDTH = 40;
const int CHARACTERBREAK_HEIGHT = 200;

const int CHARACTERDEAD_WIDTH = 30;
const int CHARACTERDEAD_HEIGHT = 300;

const int CHARACTERSURFING_WIDTH = 30;
const int CHARACTERSURFING_HEIGHT = 300;

const int SHIELDTIME_WIDTH = 60;
const int SHIELDTIME_HEIGHT = 100;

int fpsbreak = 0;
int fpsdead = 0;
int fpssurfing = 0;
int fpsshieldtime = 0;
int fpsshieldredtime = 0;
int fpsslow = 0;

bool increased = false;
void Character::SetCharacter(std::string path, SDL_Renderer* screen,const int &charactertype)
{
	//Set Detail
	this->rect.x = 800;
	this->rect.y = 400;
	this->rect.w = 40;
	this->rect.h = 40;

	this->rectshield.x = this->rect.x;
	this->rectshield.y = this->rect.y;
	this->rectshield.w = 50;
	this->rectshield.h = 50;

	this->rectbreakframe.x = 0;
	this->rectbreakframe.y = 0;
	this->rectbreakframe.w = CHARACTERBREAK_WIDTH;
	this->rectbreakframe.h = CHARACTERBREAK_HEIGHT / 5;

	this->rectdeadframe.x = 0;
	this->rectdeadframe.y = 0;
	this->rectdeadframe.w = CHARACTERDEAD_WIDTH;
	this->rectdeadframe.h = CHARACTERDEAD_HEIGHT / 10;

	this->rectsurfingframe.x = 0;
	this->rectsurfingframe.y = 0;
	this->rectsurfingframe.w = CHARACTERSURFING_WIDTH;
	this->rectsurfingframe.h = CHARACTERSURFING_HEIGHT / 10;

	this->rectshieldtime.x = 0;
	this->rectshieldtime.y = 0;
	this->rectshieldtime.w = SHIELDTIME_WIDTH;
	this->rectshieldtime.h = SHIELDTIME_HEIGHT / 10;

	this->rectshieldredtime.x = 0;
	this->rectshieldredtime.y = 0;
	this->rectshieldredtime.w = SHIELDTIME_WIDTH;
	this->rectshieldredtime.h = SHIELDTIME_HEIGHT / 10;

	this->framewidth = CHARACTER_WIDTH;
	this->frameheight = CHARACTER_HEIGHT / 3;
	this->x_float = this->rect.x;
	this->y_float = this->rect.y;
	this->speed = 1;
	this->meter = 0;
	this->aleft = this->aright = 5;
	this->left = false;
	this->right = false;
	this->brake = false;

	this->killbyboss = false;
	this->danger = false;
	this->shield = false;
	this->shieldred = false;
	//Set Link
	this->tex = LoadIMG(screen, path.c_str());
	if(charactertype==0)
	{
		this->texdead = LoadIMG(screen, "Img/Character Dead.png");
		this->texbreak = LoadIMG(screen, "Img/Character Break.png");
	}
	if(charactertype==1)
	{
		this->texdead = LoadIMG(screen, "Img/Character Green Dead.png");
		this->texbreak = LoadIMG(screen, "Img/Character Green Break.png");
	}
	if (charactertype == 2)
	{
		this->texdead = LoadIMG(screen, "Img/Character Pink Dead.png");
		this->texbreak = LoadIMG(screen, "Img/Character Pink Break.png");
	}
	this->texsurfing = LoadIMG(screen, "Img/Character Surfing.png");
	this->texshield = LoadIMG(screen, "Img/Character Shield.png");
	this->texshieldred = LoadIMG(screen, "Img/Character Shield Red.png");
	this->texshieldtime = LoadIMG(screen, "Img/Shield Time.png");
	this->texshieldredtime = LoadIMG(screen, "Img/Shield Red Time.png");
	//Set Frame Break
	for (int i = 0; i < 5; i++)
	{
		this->framebreak[i] = { rectbreakframe.x,rectbreakframe.y + i * 40,rectbreakframe.w,rectbreakframe.h };
	}
	//Set Frame Dead
	for (int i = 0; i < 10; i++)
	{
		this->framedead[i] = { rectdeadframe.x,rectdeadframe.y + i * 30,rectdeadframe.w,rectdeadframe.h };
	}
	//Set Rect Danger
	this->texdanger = LoadIMG(screen, "Img/Danger.png");
	rectdanger = { rect.x,rect.y - rect.h,30,30 };
	//Set Frame Shield Time
	for (int i = 0; i < 10; i++)
	{
		this->frameshieldtime[i] = { rectshieldtime.x,rectshieldtime.y + 10 * i,rectshieldtime.w,rectshieldtime.h };
	}
	//Set Frame Shield Red Time
	for (int i = 0; i < 10; i++)
	{
		this->frameshieldredtime[i] = { rectshieldredtime.x,rectshieldredtime.y + 10 * i,rectshieldredtime.w,rectshieldredtime.h };
	}
}
SDL_Rect Character::GetRect()
{
	return this->rect;
}
void Character::ControlCharacter(SDL_Event& event, int& SPEED, SDL_Renderer* screen, const bool& play,const bool &pause)
{
	if(!pause && play)
	switch (event.key.keysym.sym)
	{
	case SDLK_LEFT:
		if (this->rect.x >= 0)
		{
			aright = 5;
			if (left == true)
			{
				aleft += 8;
			}
			brake = false;
			right = false;
			left = true;
		}
		break;
	case SDLK_RIGHT:
		if (this->rect.x <= 1900)
		{
			aleft = 5;
			if (right == true)
			{
				aright += 8;
			}
			brake = false;
			left = false;
			right = true;
		}
		break;
	case SDLK_DOWN:
		aleft = 4;
		aright = 4;
		brake = true;
		break;
	}
}
void Character::RenderCopy(SDL_Renderer* screen, bool& play)
{
	//Check Mini
	if (mini)
	{
		timemini++;
		if (timemini != 0 && timemini % 1000 == 0)
		{
			mini = false;
			timemini = 0;
		}
		this->rect.w = 30/2;
		this->rect.h = 30/2;

		this->rectshield.w = 50/2;
		this->rectshield.h = 50/2;

		this->rectbreakframe.x = 0;
		this->rectbreakframe.y = 0;
		this->rectbreakframe.w = CHARACTERBREAK_WIDTH/2;
		this->rectbreakframe.h = CHARACTERBREAK_HEIGHT / 5/2;

		this->rectdeadframe.x = 0;
		this->rectdeadframe.y = 0;
		this->rectdeadframe.w = CHARACTERDEAD_WIDTH/2;
		this->rectdeadframe.h = CHARACTERDEAD_HEIGHT / 10/2;

		rectdanger.w = 15;
		rectdanger.h = 15;

	}
	if (fast)
	{
		if (timefast)
		{
			this->speed = this->speedcurrent + 5;
			timefast--;
		}
		else
		{
			fast = false;
			this->speed = this->speedcurrent;
			timefast = 300;
		}
	}
	else if(!mini)
	{
		this->rect.w = 30 ;
		this->rect.h = 30 ;

		this->rectshield.w = 50 ;
		this->rectshield.h = 50 ;

		this->rectbreakframe.x = 0;
		this->rectbreakframe.y = 0;
		this->rectbreakframe.w = CHARACTERBREAK_WIDTH ;
		this->rectbreakframe.h = CHARACTERBREAK_HEIGHT / 5;

		this->rectdeadframe.x = 0;
		this->rectdeadframe.y = 0;
		this->rectdeadframe.w = CHARACTERDEAD_WIDTH ;
		this->rectdeadframe.h = CHARACTERDEAD_HEIGHT / 10;

		rectdanger.w = 30;
		rectdanger.h = 30;

	}
	//Frame
	SDL_Rect* currentframebreak = &framebreak[framebreakcount];
	SDL_Rect* currentframedead = &framedead[framedeadcount];
	SDL_Rect* currentframerectshieldtime = &frameshieldtime[frameshieldtimecount];
	SDL_Rect* currentframerectshieldredtime = &frameshieldredtime[frameshieldredtimecount];
	if (!play && !killbyboss)
	{
		fpsbreak++;
		if (framebreakcount < 4 && fpsbreak % 5 == 0)
			framebreakcount++;
	}
	if (!play && killbyboss)
	{
		fpsdead++;
		if (framedeadcount < 9 && fpsdead % 5 == 0)
			framedeadcount++;
	}
	if (play && shield)
	{
		fpsshieldtime++;
		if (fpsshieldtime % 100 == 0 && frameshieldtimecount < 9)
		{
			frameshieldtimecount++;
		}
		if (frameshieldtimecount == 9)
		{
			frameshieldtimecount = 0;
			shield = false;
		}
	}
	if (play && shieldred)
	{
		fpsshieldredtime++;
		if (fpsshieldredtime % 100 == 0 && frameshieldredtimecount < 9)
		{
			frameshieldredtimecount++;
		}
		if (frameshieldredtimecount == 9)
		{
			frameshieldredtimecount = 0;
			shieldred = false;
		}
	}
	if (left == true)
	{
		moving = true;
		if (this->rect.x >= 0)
		{
			this->x_float -= aleft;
			this->rect.x = int(x_float);
			if (!brake || aleft < 0)
				aleft += 0.1;
			if (aleft > 5)
			{
				brake = true;
			}
		}
	}
	if (right == true)
	{
		moving = true;
		if (this->rect.x <= 1600-rect.w)
		{
			this->x_float += aright;
			this->rect.x = int(x_float);
			if (!brake || aright < 0)
				aright += 0.1;
			if (aright > 5)
			{
				brake = true;
			}
		}
	}
	if (brake == true)
	{
		if (left)
		{
			aleft -= 0.1;
			if (aleft < 0)
			{
				aleft = 5;
				right = false;
				left = false;
				brake = false;
				moving = false;
			}
		}

		if (right)
		{
			aright -= 0.1;
			if (aright < 0)
			{
				aright = 5;
				right = false;
				left = false;
				brake = false;
				moving = false;
			}
		}
	}
	rectdanger.x = rect.x + 2;
	rectdanger.y = rect.y - rect.h;
	rectsurfingframe.x = rect.x;
	rectsurfingframe.y = rect.y - 10;
	rectshield.x = rect.x - rectshield.w / 4 + 2;
	rectshield.y = rect.y - rectshield.h / 4;
	rectshieldtime.x = rect.x - 10;
	rectshieldtime.y = rect.y - 30;
	rectshieldredtime.x = rect.x - 10;
	rectshieldredtime.y = rect.y - 30;
	if (play)
	{
		SDL_RenderCopy(screen, tex, NULL, &rect);
	}
	else if (!play && !shieldred && !killbyboss)
	{
		SDL_RenderCopy(screen, texbreak, currentframebreak, &rect);
	}
	else if (!play && !killbyboss && !shield)
		SDL_RenderCopy(screen, texbreak, currentframebreak, &rect);
	else if (!play && killbyboss)
		SDL_RenderCopy(screen, texdead, currentframedead, &rect);
	if (danger && play)
		SDL_RenderCopy(screen, texdanger, NULL, &rectdanger);
	if (play && shield && !killbyboss)
	{
		SDL_RenderCopy(screen, texshield, NULL, &rectshield);
		SDL_RenderCopy(screen, texshieldtime, currentframerectshieldtime, &rectshieldtime);
	}
	if (play && shieldred && !killbyboss)
	{
		if (shield)
		{
			rectshieldredtime.y -= 5;
		}
		SDL_RenderCopy(screen, texshieldred, NULL, &rectshield);
		SDL_RenderCopy(screen, texshieldredtime, currentframerectshieldredtime, &rectshieldredtime);
	}
	SDL_RenderCopy(screen, texfontspeed, NULL, &rectfontspeed);
	SDL_RenderCopy(screen, texfontmeter, NULL, &rectfontmeter);
	SDL_RenderCopy(screen, texfontmetercount, NULL, &rectfontmetercount);
}
void Character::UpdateInfo(SDL_Renderer* screen, int& metercount, int& speedcount, bool& play)
{
	SDL_DestroyTexture(texfontmeter);
	SDL_DestroyTexture(texfontmetercount);
	SDL_DestroyTexture(texfontspeed);

	texfontmeter = NULL;
	texfontmetercount = NULL;
	texfontspeed = NULL;
	if (!fast)
	{
		speedcurrent = this->speed;
	}
	//Update speed
	if (speedcount % 1000 == 0 && play)
	{
		this->speed++;
		speedcount = 0;
	}
	this->speedinfo = to_string(this->speed);
	font = TTF_OpenFont("Font/Eras Demi ITC.ttf", 38);
	SDL_Rect temp = GetRectFontFromSurface(screen, font, speedinfo);
	texfontspeed = LoadFont(screen, font, speedinfo, { 255,255,255,255 });
	rectfontspeed = { 770,70,temp.w,temp.h };
	TTF_CloseFont(font);
	//Update meter 
	
	if (metercount % 1000 == 0 && play)
	{
		this->meter++;
		metercount = 0;
	}
	this->meterinfo = to_string(this->meter);
	font = TTF_OpenFont("Font/Eras Demi ITC.ttf", 38);
	temp = GetRectFontFromSurface(screen, font, meterinfo);
	texfontmeter = LoadFont(screen, font, meterinfo, { 255,255,255,255 });
	rectfontmeter = { 610,70,temp.w,temp.h };
	TTF_CloseFont(font);

	this->metercountinfo = to_string(metercount);
	font = TTF_OpenFont("Font/Century Gothic.ttf", 21);
	temp = GetRectFontFromSurface(screen, font, metercountinfo);
	texfontmetercount = LoadFont(screen,font,metercountinfo.c_str(), { 255,255,255,255 });
	rectfontmetercount = { 680,83,temp.w,temp.h };
	TTF_CloseFont(font);
}
void Character::ResetDefault()
{
	//Reset Default
	this->rect.x = 800;
	this->rect.y = 400;
	this->rect.w = 30;
	this->rect.h = 30;

	this->rectshield.x = this->rect.x;
	this->rectshield.y = this->rect.y;
	this->rectshield.w = 50;
	this->rectshield.h = 50;

	this->rectbreakframe.x = 0;
	this->rectbreakframe.y = 0;
	this->rectbreakframe.w = CHARACTERBREAK_WIDTH;
	this->rectbreakframe.h = CHARACTERBREAK_HEIGHT / 5;

	this->rectdeadframe.x = 0;
	this->rectdeadframe.y = 0;
	this->rectdeadframe.w = CHARACTERDEAD_WIDTH;
	this->rectdeadframe.h = CHARACTERDEAD_HEIGHT / 10;

	this->rectsurfingframe.x = 0;
	this->rectsurfingframe.y = 0;
	this->rectsurfingframe.w = CHARACTERSURFING_WIDTH;
	this->rectsurfingframe.h = CHARACTERSURFING_HEIGHT / 10;

	this->rectshieldtime.x = 0;
	this->rectshieldtime.y = 0;
	this->rectshieldtime.w = SHIELDTIME_WIDTH;
	this->rectshieldtime.h = SHIELDTIME_HEIGHT / 10;

	this->rectshieldredtime.x = 0;
	this->rectshieldredtime.y = 0;
	this->rectshieldredtime.w = SHIELDTIME_WIDTH;
	this->rectshieldredtime.h = SHIELDTIME_HEIGHT / 10;

	this->framewidth = CHARACTER_WIDTH;
	this->frameheight = CHARACTER_HEIGHT / 3;
	this->x_float = this->rect.x;
	this->y_float = this->rect.y;
	this->speed = 1;
	this->meter = 0;
	this->aleft = this->aright = 5;
	this->left = false;
	this->right = false;
	this->brake = false;

	this->killbyboss = false;
	this->danger = false;
	this->shield = false;
	this->shieldred = false;

	this->mini = false;
	this->fast = false;
	this->timefast = 300;
}
void Character::DestroyCharacter()
{
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(texbreak);
	SDL_DestroyTexture(texdanger);
	SDL_DestroyTexture(texdead);
}