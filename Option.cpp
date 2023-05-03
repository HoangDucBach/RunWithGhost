#include"Option.h"

Option::Option()
{
	rect.x = 475;
	rect.y = 320;
	rect.w = 664;
	rect.h = 199;

	rectadjust.x = 800;
	rectadjust.y = rect.y+86;
	rectadjust.w = 18;
	rectadjust.h = 15;

	rectblack = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	rectpause = { 228,400,1144,70 };
}
void Option::SetOption(SDL_Renderer* screen,int x,int y)
{
	setting.SetButton("Img/Option Setting Button.png", "Img/Option Setting Press Button.png", screen, { 1556,y+45,21,20 }, { 1555,y+45,21,20 });
	option.SetButton("Img/Option Rect.png", "Img/Option Press Rect.png", screen, { 1545,y+28,43,75 }, { 1545,y+38,43,75 });
	menu.SetButton("Img/Home Button Game.png", "Img/Home Button Game Press.png", screen, { x,y,47,38 }, { x,y,47,38 });
	home.SetButton("Img/Option Home Button.png", "Img/Option Home Press Button.png", screen, { 1550,y+76,33,25 }, { 1550,y+76,33,25 });
	texsetting = LoadIMG(screen, "Img/Setting.png");
	adjustrect.SetButton("Img/Adjust Rect.png", "Img/Adjust Rect.png", screen, { rect.x + 200,rect.y + 88,306,9 }, { rect.x + 200,rect.y + 88,306,9 });
	texadjust = LoadIMG(screen, "Img/Adjust Button.png");
	texblack = LoadIMG(screen, "Img/Black.png");
	texpause = LoadIMG(screen, "Img/Pause.png");
}
void Option::CheckActive(SDL_Event& event,bool &pause)
{
	menu.CheckActive(event);
	if (menu.IsSelected)
	{
		setting.CheckActive(event);
		option.CheckActive(event);
		home.CheckActive(event);
		adjustrect.CheckActive(event);
		pause = true;
	}
	else
		pause = false;
}
void Option::RenderCopy(SDL_Renderer* screen,Mouse &mouse,Sound &sound,const bool& play, const bool &RUN,const bool &pause)
{
	this->volumninfo = to_string(int(float(sound.volumn * 100) / 128));
	this->volumninfo += "%";
	TTF_Font* font = TTF_OpenFont("Font/Century Gothic.ttf", 15);
	SDL_Rect temp = GetRectFontFromSurface(screen, font, volumninfo);
	rectfontvolumn = { rectadjust.x,420,temp.w,temp.h };
	SDL_DestroyTexture(texfontvolumn);
	texfontvolumn = LoadFont(screen, font, volumninfo, { 93,92,90,255 });
	TTF_CloseFont(font);
	menu.UpdateButton(mouse);
	if (menu.IsSelected)
	{
		option.UpdateButton(mouse);
		option.RenderCopy(screen);
		if (!setting.IsPoint)
			home.UpdateButton(mouse);
		if (!home.IsPoint)
			setting.UpdateButton(mouse);
		home.RenderCopy(screen);
		setting.RenderCopy(screen);
		if (RUN && play && pause)
			SDL_RenderCopy(screen, texpause, NULL, &rectpause);
		if (setting.IsSelected)
		{
			adjustrect.UpdateButton(mouse);
			SDL_RenderCopy(screen, texblack, NULL,&rectblack );
			SDL_RenderCopy(screen, texsetting, NULL, &rect);
			adjustrect.RenderCopy(screen);
			SDL_RenderCopy(screen, texadjust, NULL, &rectadjust);
			SDL_RenderCopy(screen, texfontvolumn, NULL, &rectfontvolumn);
		}
	}
	else
	{
		setting.IsSelected = false;
		home.IsSelected = false;
	}
	menu.RenderCopy(screen);
}
void Option::DestroyOption()
{	
	home.IsSelected = false;
	setting.IsSelected = false;
}
void Option::AdjustVolumn(SDL_Renderer* screen,Mouse& mouse,Sound& sound)
{
	if (setting.IsSelected && adjustrect.IsPoint)
	{
		rectadjust.x = mouse.rect.x;
		if (rectadjust.x < 675)
			rectadjust.x = 675;
		if (rectadjust.x > 675 + 290)
			rectadjust.x = 675 + 290;
		sound.volumn = int((rectadjust.x - 675) * 128 / 290);
		sound.AdjustVolumn();
	}
}