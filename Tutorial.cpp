#include"Tutorial.h"
const int move = 25;
Tutorial::~Tutorial()
{
	delete homebutton;
	delete viewbutton;
	delete settingbutton;
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(texbosstutor);
	SDL_DestroyTexture(texcharactertutor);
	SDL_DestroyTexture(texfireareatutor);
	SDL_DestroyTexture(texmagictutor);
	SDL_DestroyTexture(texobstacletutor);
	SDL_DestroyTexture(texopenview);
	SDL_DestroyTexture(texrobottutor);
	SDL_DestroyTexture(texRWG);
}
void Tutorial::SetTutorial(SDL_Renderer* screen)
{
	//Memory Allocation
	homebutton = new Button();
	settingbutton = new Button();
	viewbutton = new Button();
	//Set Detail
	rect.x = 0;
	rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;

	rectopenview.x = 18;
	rectopenview.y = 0;
	rectopenview.w = 1582;
	rectopenview.h = 902;

	rectplayer.x =0;
	rectplayer.y = 960;
	rectplayer.w = 1533;
	rectplayer.h = 960;

	rectobstacletutor.x = 200;
	rectobstacletutor.y = 1000;
	rectobstacletutor.w = 1388;
	rectobstacletutor.h = 872;

	rectmagictutor.x = 0;
	rectmagictutor.y = 1000;
	rectmagictutor.w = 1536;
	rectmagictutor.h = 960;

	rectbosstutor.x = 16;
	rectbosstutor.y = 1000;
	rectbosstutor.w = 1466;
	rectbosstutor.h = 722;

	rectrobottutor.x = 189;
	rectrobottutor.y = 1000;
	rectrobottutor.w = 1318;
	rectrobottutor.h = 648;

	rectfireareatutor.x = 0;
	rectfireareatutor.y = 0;
	rectfireareatutor.w = 1600;
	rectfireareatutor.h = 960;

	rectRWG.x = 13;
	rectRWG.y = -20;
	rectRWG.w = 100;
	rectRWG.h = 100;

	//Set Link
	this->tex = LoadIMG(screen, "Img/Tutorial.png");
	this->texopenview = LoadIMG(screen, "Img/Open View.png");
	this->texcharactertutor = LoadIMG(screen, "Img/Character Tutorial.png");
	this->texobstacletutor = LoadIMG(screen, "Img/Obstacle Tutorial.png");
	this->texmagictutor = LoadIMG(screen, "Img/Magic Tutorial.png");
	this->texbosstutor = LoadIMG(screen, "Img/Boss Tutorial.png");
	this->texrobottutor = LoadIMG(screen, "Img/Robot Tutorial.png");
	this->texRWG = LoadIMG(screen, "Img/RWG.png");
	this->texfireareatutor = LoadIMG(screen, "Img/Fire Area.png");
	//Set Sound
	backgroundmusic.SetSound("Sound/Tutorial Sound.mp3",2, true);
	//Build Home Button
	(*homebutton).SetButton("Img/Home Button Game.png", "Img/Home Button Game Press.png", screen, { 1544,11,47,38 }, { 1544,11,47,38 });
	//Build Settings Button
	(*settingbutton).SetButton("Img/Settings Button Game.png", "Img/Settings Button Game Press.png", screen, { 1544,55,47,38 }, { 1544,55,47,38 });
	//Build View Setting
	(*viewbutton).SetButton("Img/View Button.png", "Img/View Button Press.png", screen, { 715,774,140,54 }, { 715,774,140,54 });

}
void Tutorial::RenderCopy(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, tex, NULL, &rect);
	SDL_RenderCopy(screen, texopenview, NULL, &rectopenview);
	SDL_RenderCopy(screen, texcharactertutor, NULL, &rectplayer);
	SDL_RenderCopy(screen, texobstacletutor, NULL, &rectobstacletutor);
	SDL_RenderCopy(screen, texmagictutor, NULL, &rectmagictutor);
	SDL_RenderCopy(screen, texbosstutor, NULL, &rectbosstutor);
	SDL_RenderCopy(screen, texrobottutor, NULL, &rectrobottutor);
	SDL_RenderCopy(screen, texfireareatutor, NULL, &rectfireareatutor);
	SDL_RenderCopy(screen, texRWG, NULL, &rectRWG);
}
void Tutorial::MouseWheel(SDL_Event &event)
{
	if((RUN))
	{
		if (event.wheel.y < 0)
		{
			up = true;
		}
		else
		{
			down = true;
		}
	}
}
void Tutorial::UpdateCoordinate()
{
	if(RUN)
	{
		if (up && MOVEDOWN == 960 && rectfireareatutor.y != 0)
		{
			rectopenview.y -= 20;
			MOVEUP -= 20;
			if (MOVEUP == 0)
			{
				up = false;
				MOVEUP = 960;
			}
		}
		else if (down && rectopenview.y != 0 && MOVEUP == 960)
		{
			rectopenview.y += 20;
			MOVEDOWN -= 20;
			if (MOVEDOWN == 0)
			{
				down = false;
				MOVEDOWN = 960;
			}
		}
		(*viewbutton).rect.y = rectopenview.y + 774;
		rectplayer.y = rectopenview.y + 960;
		rectobstacletutor.y = rectplayer.y + 960;
		rectbosstutor.y = rectobstacletutor.y + 960 + 190;
		rectrobottutor.y = rectbosstutor.y + 960 + 100;
		rectfireareatutor.y = rectrobottutor.y + 960 - 290;
	}

}
void Tutorial::RunTutorial(SDL_Renderer* screen,SDL_Event &event,Mouse &mouse,Settings &settings, bool& check, Sound& sound)
{
	backgroundmusic.Play();
	while (RUN)
	{
		backgroundmusic.volumn = sound.volumn;
		backgroundmusic.AdjustVolumn();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				RUN = false;
			}
			if (event.type == SDL_MOUSEWHEEL)
			{
				MouseWheel(event);
			}
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (!(*settingbutton).IsPoint)
					(*homebutton).CheckActive(event);
				if (!(*homebutton).IsPoint)
					(*settingbutton).CheckActive(event);
				if (settings.RUN)
				{
					settings.exitbutton.CheckActive(event);
					settings.speakerbutton.CheckActive(event);
					settings.mutebutton.CheckActive(event);
				}
				(*viewbutton).CheckActive(event);
			}
		}
		if ((*viewbutton).IsSelected)
		{
			rectopenview.y -= 20;
			MOVEUP -= 20;
			if (MOVEUP == 0)
			{
				up = false;
				MOVEUP = 960;
				(*viewbutton).IsSelected = false;
			}
		}
		UpdateCoordinate();
		RenderCopy(screen);
		(*homebutton).UpdateButton(mouse);
		(*homebutton).RenderCopy(screen);
		(*settingbutton).UpdateButton(mouse);
		(*settingbutton).RenderCopy(screen);
		(*viewbutton).UpdateButton(mouse);
		(*viewbutton).RenderCopy(screen);
		settings.RenderCopy(screen, mouse);
		settings.UpdateAll(screen, event, mouse, sound);
		if ((*settingbutton).IsSelected)
		{
			settings.RUN = true;
			(*settingbutton).IsSelected = false;
		}
		if ((*homebutton).IsSelected)
		{
			DestroyTutorial();
			backgroundmusic.Pause();
			this->RUN = false;
			check = false;
			(*homebutton).IsSelected = false;
			rectopenview.y = 0;
		}
		mouse.UpdateMouse();
		mouse.RenderCopy(screen);
		SDL_RenderPresent(screen);
	}
}
void Tutorial::DestroyTutorial()
{
	RUN = false;
	backgroundmusic.Stop();
}
