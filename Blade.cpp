#include"Blade.h"
void Blade::SetBlade(SDL_Renderer* screen,const bool &vertical)
{
	//Set Ver or Hoz
	this->vertical = vertical;
	//Set Detail
	this->rect.x = ((Random(0, 1))?0:1600);
	this->rect.y = 1000;
	this->rect.w = 40;
	this->rect.h = 40;

	//Set Link
	tex = LoadIMG(screen, "Img/Blade.png");
	if(vertical)
	{
		texhub = LoadIMG(screen, "Img/Hub Vertical.png");
		this->recthub.x = Random(- 1000,-100);
		this->recthub.y = 0;
		this->recthub.w = 4;
		this->recthub.h = 960;
	}
	else
	{
		texhub = LoadIMG(screen, "Img/Hub.png");
		this->recthub.x = 0;
		this->recthub.y = Random(1000,5000);
		this->recthub.w = 1600;
		this->recthub.h = 4;
	}
	//Set Frame
	for (int i = 0; i < 8; i++)
	{
		rectframe[i] = { 0,i * 40,40,40 };
	}
}
void Blade::ImpactBlade(Character& character,bool &play,bool &shield)
{
	SDL_Rect temp = character.GetRect();
	SDL_Rect check;
	if (play && !shield)
	{
		if ((temp.x + temp.w / 2) >= rect.x && temp.x <= (rect.x + rect.w) && (temp.y + temp.h) > (rect.y + 1 / 2 * rect.h) && SDL_HasIntersection(&temp, &rect))
		{
			play = false;
			character.aleft = 0;
			character.aright = 0;
		}
	}
}
void Blade::AnimationBlade(const float& speed)
{
	if (vertical)
	{
		if(!change)
			this->rect.y -= 3;
		else
			this->rect.y += 3;
		if (this->rect.y <= 0)
			change = true;
		if (this->rect.y >= 960)
			change = false;
		x_float += speed;
		this->rect.x = (int)x_float;
		if (rect.x >= 1700)
		{
			x_float = Random(-1000, -1500);
		}
		fps++;
		this->recthub.y = 0;
		this->recthub.x = this->rect.x + this->rect.w / 2;
	}
	else
	{
		if(!change)
			this->rect.x += 3;
		else
			this->rect.x -= 3;
		if (this->rect.x >= 1700)
			change = true;
		if (this->rect.x <= 0)
			change = false;
		y_float -= speed;
		this->rect.y = (int)y_float;
		if (rect.y <= -150)
		{
			y_float = Random(1000, 5000);
		}
		fps++;
		this->recthub.x = 0;
		this->recthub.y = this->rect.y + this->rect.h / 2;
	}
}
void Blade::RenderCopy(SDL_Renderer* screen)
{
	if (fps % 1 == 0)
	{
		framecount++;
		fps = 1;
	}
	if (framecount == 7)
		framecount = 0;
	SDL_Rect* currentframe = &rectframe[framecount];
	SDL_RenderCopy(screen, texhub, NULL, &recthub);
	SDL_RenderCopy(screen, tex,currentframe, &rect);
}
void Blade::ResetDefault()
{
	//Reset Detail
	this->rect.x = 0;
	this->rect.y = 1000;
	this->rect.w = 40;
	this->rect.h = 40;

	this->x_float = this->rect.x;
	this->y_float = this->rect.y;
	if (vertical)
	{
		this->recthub.x = -100;
		this->recthub.y = 0;
		this->recthub.w = 4;
		this->recthub.h = 960;
	}
	else
	{
		this->recthub.x = 0;
		this->recthub.y = 1000;
		this->recthub.w = 1600;
		this->recthub.h = 4;
	}
}