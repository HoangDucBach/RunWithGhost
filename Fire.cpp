#include"Fire.h"
void Fire::SetFire(SDL_Renderer* screen)
{
	//Set Detail
	rect.w = 1725;
	rect.h = 1725;
	rect.x = SCREEN_WIDTH / 2 - rect.w / 2;
	rect.y = SCREEN_HEIGHT / 2 - rect.h / 2;

	r = rect.w / 2;
	//Set Link
	tex = LoadIMG(screen, "Img/Fire.png");
}
void Fire::RenderCopy(SDL_Renderer* screen)
{
	if(time)
		SDL_RenderCopy(screen, tex, NULL, &rect);
}
void Fire::Minimum()
{
	if (r >= 100)
	{
		fps++;
		if (fps % 5 == 0)
		{
			rect.w -= 1;
			rect.h -= 1;
			fps = 1;
		}
	}
	else
		time--;
	r = rect.w / 2;
	if (time == 0)
		RUN = false;
	rect.x = SCREEN_WIDTH / 2 - r;
	rect.y = SCREEN_HEIGHT/ 2 - r;
}
void Fire::CheckDanger(Character& character, bool& play)
{
	if (Distance(rect, character.GetRect()) > r)
		play = false;
}
void Fire::ResetDefault()
{
	//Reset Detail
	rect.w = 1725;
	rect.h = 1725;
	rect.x = SCREEN_WIDTH / 2 - rect.w / 2;
	rect.y = SCREEN_HEIGHT / 2 - rect.h / 2;

	r = rect.w / 2;
	RUN = false;
}