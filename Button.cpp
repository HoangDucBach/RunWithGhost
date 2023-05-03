#include"Function.h"
#include"Button.h"
void Button::SetButton(std::string path1, std::string path2,SDL_Renderer* screen, const SDL_Rect& rect_, const SDL_Rect& rectreplace_)
{
		rect.h = rect_.h;
		rect.w = rect_.w;
		rect.x = rect_.x;
		rect.y = rect_.y;

		rectreplace.h = rectreplace_.h;
		rectreplace.w = rectreplace_.w;
		rectreplace.x = rectreplace_.x;
		rectreplace.y = rectreplace_.y;
	
		tex = LoadIMG(screen, path1.c_str());
		texreplace = LoadIMG(screen, path2.c_str());
}
void Button::UpdateButton(Mouse& mouse)
{
	SDL_Rect check;
	SDL_Rect temp = mouse.rect;
	if (SDL_IntersectRect(&temp,&rect,&check))
	{
		if(check.w*check.h>100)
		{
			IsPoint = true;
		}
	}
	else
	{
		IsPoint = false;
	}
}
void Button::CheckActive(SDL_Event& event)
{
	bool temp = true;
	if (event.button.button == SDL_BUTTON_LEFT && IsPoint)
	{
		if(IsSelected==false && temp)
		{
			IsSelected = true;
			temp = false;
		}
		if (IsSelected == true && temp)
		{
			IsSelected = false;
			temp = false;
		}
		std::cout << IsSelected << "\n";
	}
}
void Button::RenderCopy(SDL_Renderer* screen)
{
	if(!IsPoint)
		SDL_RenderCopy(screen, tex, NULL, &rect);
	else
		SDL_RenderCopy(screen, texreplace, NULL, &rectreplace);
}
void Button::DestroyButton()
{
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(texreplace);
	IsPoint = false;
	IsSelected = false;
}