#include"Home.h"
const int RWG_WIDTH = 573;
const int RWG_HEIGHT = 2790;

int fpsrwg = 0;
int currentcharacter = 0;

bool playmusic = false;

Home::Home()
{
	rectrwg.x = 45;
	rectrwg.y = 280;
	rectrwg.w = RWG_WIDTH;
	rectrwg.h = RWG_HEIGHT / 45;
}
void Home::SetHome(SDL_Renderer* screen)
{
	//Set Best 
	std::fstream file_input;
	file_input.open("Input.INP");
	file_input >> BESTSCORE;
	file_input >> BESTSPEED;
	file_input.close();
	//Set Sound
	backgroundmusic.SetSound("Sound/Home Sound.mp3",0,false);
	//Set Background
	background.LoadBackground("Img/Home.png", screen);
	//Set Play Button
	play.SetButton("Img/Play Button.png","Img/Play Button Press.png",screen,{42,500,144,45},{42,500,151,47});
	//Set Mouse
	mouse.SetMouse(screen);
	//Set Settings
	settings.SetSettings(screen);
	//Set Exit Button
	exitbutton.SetButton("Img/Exit Button.png", "Img/Exit Button Press.png", screen, {SCREEN_WIDTH-52,0,52,52}, { SCREEN_WIDTH - 52,0,52,52 });
	//Set Settings Button
	settingsbutton.SetButton("Img/Settings Button.png", "Img/Settings Button Press.png", screen, { SCREEN_WIDTH - 52 * 2,0,52,52 }, { SCREEN_WIDTH - 52 * 2,0,52,52 });
	//Set Tutorial
	tutorialbutton.SetButton("Img/Tutorial Button.png", "Img/Tutorial Press Button.png", screen, { 200,500,144,48 }, { 200,500,144,48 });
	//Set Run With Ghost Animation
	texrwg = LoadIMG(screen, "Img/Run With Ghost Frame.png");
	for (int i = 0; i < 44; i++)
		framerwg[i] = { 0,i * rectrwg.h,rectrwg.w ,rectrwg.h };
	//Set Character
	texcs = new SDL_Texture * ();
	texcs[0] = LoadIMG(screen, "Img/Character Select Frame.png");
	texcs[1] = LoadIMG(screen, "Img/Character Select Green Frame.png");
	texcs[2] = LoadIMG(screen, "Img/Character Select Pink Frame.png");
	for(int i=0;i<3;i++)
		rectcs[i] = {1035 + 125 * i,550,80,80};
	for (int i = 0; i < 3; i++)
	{
		for(int j=0;j<24;j++)
			rectcsf[i][j] = {0,80 * j,80,80};
	}
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			texcharacter[i] = LoadIMG(screen, "Img/Character.png");
			rectcharacterlist[i] = { 1250,810,80,80 };
		}
		if (i == 1)
		{
			texcharacter[i] = LoadIMG(screen, "Img/Character Green.png");
			rectcharacterlist[i] = { 1250,810,80,80 };
		}
		if (i == 2)
		{
			texcharacter[i] = LoadIMG(screen, "Img/Character Pink.png");
			rectcharacterlist[i] = { 1250,810,80,80 };
		}
	}
	//Set Button Select
	buttonselect[0].SetButton("Img/Button Select.png", "Img/Button Select Press.png", screen, { 1030,552,89,84 }, { 1030,552,89,84 });
	buttonselect[1].SetButton("Img/Button Select Green.png", "Img/Button Select Green Press.png", screen, { 1030+120+5,552,89,84 }, { 1030 + 120+5,552,89,84 });
	buttonselect[2].SetButton("Img/Button Select Pink.png", "Img/Button Select Pink Press.png", screen, { 1030 + 120*2+10,552,89,84 }, { 1030 + 120*2+10,552,89,84 });
	//Set Current
	texcurrent = LoadIMG(screen, "Img/Select Current.png");
	rectcurrent = { buttonselect[0].rect.x + buttonselect[0].rect.w / 2 - 29/2,buttonselect[0].rect.y - 33,29,152 };
}
void Home::UpdateAll(SDL_Renderer* screen)
{
	SDL_Rect* tmp = new SDL_Rect();
	TTF_Font* font = TTF_OpenFont("Font/Century Gothic Bold.ttf", 31);
	*tmp = GetRectFontFromSurface(screen, font, BESTSCORE);
	rectbestscore = { 1008,286,tmp->w,tmp->h };
	texbestscore = LoadFont(screen, font, BESTSCORE, { 189,186,186,255 });
	*tmp = GetRectFontFromSurface(screen, font, BESTSPEED);
	rectbestspeed = { 1245,286,tmp->w,tmp->h };
	texbestspeed= LoadFont(screen, font, BESTSPEED, { 189,186,186,255 });
	delete tmp;
	TTF_CloseFont(font);
	SDL_RenderCopy(screen, texbestspeed, NULL, &rectbestspeed);
	SDL_DestroyTexture(texbestspeed);
	SDL_RenderCopy(screen, texbestscore, NULL, &rectbestscore);
	SDL_DestroyTexture(texbestscore);
}
void Home::CharacterSelectRenderCopy(SDL_Renderer* screen)
{
	fpsrwg++;
	for (int i = 0; i < 3; i++)
	{
		if (buttonselect[i].IsSelected)
		{
			buttonselect[currentcharacter].IsSelected = false;
			currentcharacter = i;
			rectcurrent.x = buttonselect[i].rect.x + buttonselect[i].rect.w / 2-rectcurrent.w/2;
			rectcurrent.y = buttonselect[i].rect.y -33;
		}
	}
	if (fpsrwg % 10 == 0)
	{
		for(int i=0;i<3;i++)
		{
			if (buttonselect[i].IsPoint)
				framecountcs[i]++;
			else
				framecountcs[i] = 0;
		}
		fpsrwg = 1;
	}
	for (int i = 0; i < 3; i++)
	if (framecountcs[i] == 24)
		framecountcs[i] = 0;
	for(int i=0;i<3;i++)
	currentframecs[i] = &rectcsf[i][framecountcs[i]];
	for (int i = 0; i < 3; i++)
	{
		buttonselect[i].UpdateButton(mouse);
		buttonselect[i].RenderCopy(screen);
	}
	for(int i=0;i<3;i++)
		SDL_RenderCopy(screen, texcs[i], currentframecs[i], &rectcs[i]);
	SDL_RenderCopy(screen, texcurrent, NULL, &rectcurrent);
}
void Home::RenderCopy(SDL_Renderer* screen,SDL_Event& event,SDL_Window* window)
{
	SetHome(screen);
	while (RUN)
	{
		if (!playmusic)
		{
			backgroundmusic.Play();
			playmusic = true;
		}
		background.RenderCopy(screen,NULL);
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				RUN = false;
			}
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				play.CheckActive(event);
				exitbutton.CheckActive(event);
				settingsbutton.CheckActive(event);
				for (int i = 0; i < 3; i++)
					buttonselect[i].CheckActive(event);
				if(settings.RUN)
				{
					settings.exitbutton.CheckActive(event);
					settings.speakerbutton.CheckActive(event);
					settings.mutebutton.CheckActive(event);
				}
				tutorialbutton.CheckActive(event);
			}
			if (event.type == SDL_MOUSEWHEEL)
			{
				if(settings.RUN)
				{
					settings.AdjustVolumn(screen, event, mouse, backgroundmusic);
				}
			}
		}
		play.UpdateButton(mouse);
		play.RenderCopy(screen);
		exitbutton.UpdateButton(mouse);
		exitbutton.RenderCopy(screen);
		settingsbutton.UpdateButton(mouse);
		settingsbutton.RenderCopy(screen);
		tutorialbutton.UpdateButton(mouse);
		tutorialbutton.RenderCopy(screen);
		CharacterSelectRenderCopy(screen);
		UpdateAll(screen);
		settings.RenderCopy(screen, mouse);
		settings.UpdateAll(screen, event, mouse, backgroundmusic);
		mouse.UpdateMouse();
		mouse.RenderCopy(screen);
		if (settingsbutton.IsSelected)
		{
			settings.RUN = true;
			settingsbutton.IsSelected = false;
		}
		if (exitbutton.IsSelected)
		{
			RUN = false;
			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
			return;
		}
		if (tutorialbutton.IsSelected)
		{
			backgroundmusic.Pause();
			playmusic = false;
			tutorial = new Tutorial();
			(*tutorial).SetTutorial(screen);
			(*tutorial).RUN = true;
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_MOUSEWHEEL)
					(*tutorial).MouseWheel(event);
			}
			(*tutorial).RunTutorial(screen,event,mouse,settings,tutorialbutton.IsSelected,backgroundmusic);
			delete tutorial;
			
		}
		if (play.IsSelected)
		{
			backgroundmusic.Pause();
			playmusic = false;
			game = new Game();
			(*game).RUN = true;
			(*game).homebutton.IsSelected = false;
			(*game).SetGame(screen, mouse, currentcharacter);
			(*game).RunGame(screen, mouse, play.IsSelected, currentcharacter, backgroundmusic, settings, BESTSCORE, BESTSPEED);
			delete game;
		}
		else
		{
			backgroundmusic.Resume();
		}
		SDL_RenderPresent(screen);
	}
}