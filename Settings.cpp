#include"Settings.h"
void Settings::SetSettings(SDL_Renderer* screen)
{
	//Set Detail
	rect.w = 688;
	rect.h = 396;
	rect.x = SCREEN_WIDTH/2 - rect.w / 2;
	rect.y = SCREEN_HEIGHT/2 - rect.h / 2;

	rectnode.x = rect.x+200+155;
	rectnode.y = rect.y+130;
	rectnode.w = 9;
	rectnode.h = 9;
	//Set Link
	tex = LoadIMG(screen, "Img/Setting GUI.png");
	texnode = LoadIMG(screen, "Img/Node.png");
	//Set Exit Button
	exitbutton.SetButton("Img/Exit Settings Button.png", "Img/Exit Settings Button Press.png", screen, { rect.x + rect.w-28-7,rect.y ,28,28 }, { rect.x + rect.w - 28-7,rect.y,28,28 });
	//Set Speaker Button
	speakerbutton.SetButton("Img/Speaker Icon.png", "Img/Speaker Icon.png", screen, { rect.x + 160,rect.y + 125,28,22 }, { rect.x + 160,rect.y + 125,28,22 });
	//Set Mute Button
	mutebutton.SetButton("Img/Mute Icon.png", "Img/Mute Icon.png", screen, { rect.x + 160,rect.y + 125,25,23 }, { rect.x + 160,rect.y + 125,25,23 });
}
void Settings::RenderCopy(SDL_Renderer* screen,Mouse &mouse)
{
	if(RUN)
	{
		SDL_RenderCopy(screen, tex, NULL, &rect);
		rectfillleft = { rect.x + 200,rectnode.y+2,rectnode.x-rect.x-200,4};
		rectfillright = { rectnode.x,rectnode.y+3,rect.x+510-rectnode.x,2};
		SDL_SetRenderDrawColor(screen, 118, 255, 247, 255);
		SDL_RenderFillRect(screen,&rectfillleft);
		SDL_SetRenderDrawColor(screen, 163, 162, 162, 255);
		SDL_RenderFillRect(screen, &rectfillright);
		SDL_RenderCopy(screen, texnode, NULL, &rectnode);
		TTF_Font* font = TTF_OpenFont("Font/Century Gothic.ttf", 23);
		texfontvolumn = LoadFont(screen, font, volumninfo, { 208,208,208,255 });
		SDL_Rect* temp=new SDL_Rect();
		(*temp)=GetRectFontFromSurface(screen, font, volumninfo);
		rectfont = {rect.x+520,rectnode.y- (*temp).w/2,(*temp).w,(*temp).h};
		SDL_RenderCopy(screen, texfontvolumn, NULL, &rectfont);
		exitbutton.UpdateButton(mouse);
		exitbutton.RenderCopy(screen);
		speakerbutton.UpdateButton(mouse);
		mutebutton.UpdateButton(mouse);
		if(speakerbutton.IsSelected || volumninfo=="0")
		{
			mutebutton.RenderCopy(screen);
		}
		else
		{
			speakerbutton.RenderCopy(screen);
		}
		if (exitbutton.IsSelected)
		{
			RUN = false;
			exitbutton.IsSelected = false;
		}
		SDL_DestroyTexture(texfontvolumn);
		TTF_CloseFont(font);
		delete temp;
	}
}
void Settings::AdjustVolumn(SDL_Renderer *screen,SDL_Event &event,Mouse &mouse,Sound& sound)
{	
	if (event.wheel.y > 0)
	{
		if (rectnode.x <= rect.x + 510)
			rectnode.x += 2;
	}
	else
	{
		if (rectnode.x >= rect.x + 200)
			rectnode.x -= 2;
	}
	volumn = rectfillleft.w * 100 / (rectfillleft.w + rectfillright.w);
}
void Settings::UpdateAll(SDL_Renderer* screen, SDL_Event& event, Mouse& mouse, Sound& sound)
{
	if (speakerbutton.IsSelected)
	{
		sound.volumn = 0;
	}
	else
		sound.volumn = volumn;
	sound.AdjustVolumn();
	volumninfo = to_string(volumn);
	if (volumn == 0) volumninfo = "0";
}