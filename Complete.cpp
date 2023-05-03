#include"Complete.h"
bool playedgameoversound = false;
void Complete::SetComplete(SDL_Renderer* screen)
{
	//Set Detail
	rect.w = 399;
	rect.h = 323;
	rect.x = 800 - rect.w / 2;
	rect.y = 450 - rect.h / 2;

	rectadjust.x = 800;
	rectadjust.y = 428;
	rectadjust.w = 18;
	rectadjust.h = 15;
	//Set Link
	tex = LoadIMG(screen, "Img/Score.png");
	//Set Detail
	show = false;
	//Build 2 Button
	this->again.SetButton("Img/Play Again Button.png", "Img/Play Again Button Press.png",screen,{ rect.x+170,rect.y+210,67,67 },{ rect.x + 170,rect.y + 210,67,67 });
	//Set Game Over Sound
	gameoversound.SetSound("Sound/Game Over Sound.wav", 2, true);
}
void Complete::UpdateComplete(SDL_Renderer* screen, Character& character,int &metercount,Sound &sound)
{
	SDL_DestroyTexture(texfontmeter);
	SDL_DestroyTexture(texfontspeed);
	//Build Info
	this->meterinfo = to_string(character.meter);
	this->meterinfo += "km" + to_string(metercount) + "m";
	this->speedinfo = to_string(character.speed);
	font = TTF_OpenFont("Font/Eras Bold ITC.ttf", 51);
	SDL_Rect temp=GetRectFontFromSurface(screen,font, meterinfo);
	rectfontmeter = { rect.x+70,rect.y+35,temp.w,temp.h };
	texfontmeter = LoadFont(screen,font,meterinfo, { 159,247,252,255 });
	TTF_CloseFont(font);
	font = TTF_OpenFont("Font/Century Gothic Bold.ttf", 76);
	temp=GetRectFontFromSurface(screen,font,speedinfo);
	rectfontspeed = { rect.x+85,rect.y+120,temp.w,temp.h };
	texfontspeed = LoadFont(screen, font, speedinfo, { 186,186,186,255 });
	TTF_CloseFont(font);
}
void Complete::CheckActive(SDL_Event& event)
{
	if(show)
	{
		again.CheckActive(event);
	}
}
void Complete::RenderCopy(SDL_Renderer* screen, Mouse& mouse, const std::string &bestscore)
{
	font = TTF_OpenFont("Font/Century Gothic Bold.ttf", 20);
	SDL_Rect* tmp = new SDL_Rect();
	*tmp=GetRectFontFromSurface(screen, font, bestscore);
	SDL_Rect tmp1 ;
	tmp1 = { 860,428,tmp->w,tmp->h };
	SDL_Texture* textmp;
	textmp=LoadFont(screen, font, bestscore, { 189,186,186,255 });
	delete tmp;
	TTF_CloseFont(font);
	if(!playedgameoversound)
	{
		gameoversound.Play();
		playedgameoversound = true;
	}
	SDL_RenderCopy(screen, tex, NULL, &rect);
	SDL_RenderCopy(screen, texfontmeter, NULL, &rectfontmeter);
	SDL_RenderCopy(screen, texfontspeed, NULL, &rectfontspeed);
	SDL_RenderCopy(screen, textmp, NULL, &tmp1);
	SDL_DestroyTexture(textmp);
	again.UpdateButton(mouse);
	again.RenderCopy(screen);
}
void Complete::DestroyComplete()
{
	gameoversound.Stop();
	playedgameoversound = false;
	again.DestroyButton();
}