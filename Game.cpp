#include"Game.h"
Game::~Game()
{
	delete character;
	delete [] rectpauseframe;
	delete complete;
	VectorObs.clear();
	VectorObsMove.clear();
	Obstacle.clear();
	SDL_DestroyTexture(texbackground);
	SDL_DestroyTexture(texcount);
	SDL_DestroyTexture(texinfo);
	SDL_DestroyTexture(texpause);

};
void Game::SetGame(SDL_Renderer* screen, Mouse& mouse,const int& charactertype)
{
	//Memory Allocation
	character = new Character();
	complete = new Complete();
	rectpauseframe = new SDL_Rect[2];
	srand(time(NULL));
	//Set Global Variable
	COUNT = 3;
	SPEEDCOUNT = 0;
	METERCOUNT = 0;
	COUNTCOUNT = 1;
	COUNTTIME = 1;
	LEVEL = 1;
	this->PLAY = true;
	this->PAUSE = false;
	//Build VectorObsMove
	for (int i = 0; i < SizeVOM; i++)
	{
		Object obj({ Random(-100,2000),Random(1700,3000),66,11 });
		obj.SetObject("Img/Box.png", screen);
		VectorObsMove.push_back(obj);
	}
	//Build VectorObs
	for (int i = 0; i < 40; i++)
	{
		int index = Random(0, 1);
		if (index == 0)
		{
			Object obj({ Random(-100,2000),Random(1700,3000),61,22});
			obj.SetObject(Obstacle[0], screen);
			VectorObs.push_back(obj);
			continue;
		}
		if (index == 1)
		{
			Object obj({ Random(-100,2000),Random(1700,3000),32,37});
			obj.SetObject(Obstacle[1], screen);
			VectorObs.push_back(obj);
			continue;
		}
	}
	//Build Character
	if(charactertype==0)
		(*character).SetCharacter("Img/Character.png", screen, charactertype);
	if(charactertype==1)
		(*character).SetCharacter("Img/Character Green.png", screen, charactertype);
	if(charactertype==2)
		(*character).SetCharacter("Img/Character Pink.png", screen, charactertype);
	//Build Boss
	boss.SetBoss("Img/Boss Frame.png",screen);
	//Build Background
	background.LoadBackground("Img/Background Game.png", screen);
	//Build Mouse
	mouse.SetMouse(screen);
	//Build Complete
	(*complete).SetComplete(screen);
	//Build Shield
	shield.SetObjectCollect("Img/Shield Frame.png", { 800,2000,50,50 }, screen);
	//Build Shield Red
	shieldred.SetObjectCollect("Img/Shield Red Frame.png", { 100,2500,50,50 }, screen);
	//Build Mini
	mini.SetObjectCollect("Img/Mini.png", { 1400,3000,50,50 }, screen);
	//Build Big
	fast.SetObjectCollect("Img/Big.png", { 400,5000,50,50 }, screen);
	//Build Boss Rambo
	bossrambo.SetBossRambo(screen);
	//Set Bullet
	bullets.clear();
	for (int i = 0; i < 5; i++)
	{
		Bullet bullet;
		bullet.SetBullet(screen);
		bullets.push_back(bullet);
	}
	//Build Blade
	for(int i=0;i<6;i++)
	{
		Blade blade;
		blade.SetBlade(screen, Random(0,1));
		blades.push_back(blade);
	}
	//Build Fire Area
	fire.SetFire(screen);
	//Build Home Button
	homebutton.SetButton("Img/Home Button Game.png", "Img/Home Button Game Press.png", screen, { 1544,11,47,38 }, { 1544,11,47,38 });
	//Build Settings Button
	settingbutton.SetButton("Img/Settings Button Game.png", "Img/Settings Button Game Press.png", screen, { 1544,55,47,38 }, { 1544,55,47,38 });
	//Build Background Music
	backgroundmusic.SetSound("Sound/Game Sound.mp3", 1,true);
	//Build Infomation Game
	rectinfo = { 611,4,325,116 };
	//Build Background Game
	rectbackground = { 0,0,1600,960};
	background.LoadBackground("Img/Background Game.png", screen);
	backgroundfire.LoadBackground("Img/Background Fire Game.png", screen);
	//Build Pause
	texpause = LoadIMG(screen, "Img/Pause.png");
	rectpauseframe[0] = { 0,0,100,100 };
	rectpauseframe[1] = { 0,100,100,100 };
	rectpause = { 1515,60,100,100 };

}
void Game::ResetGame(SDL_Renderer*screen,const int & charactertype)
{
	//Set Global Variable
	COUNT = 3;
	SPEEDCOUNT = 0;
	METERCOUNT = 0;
	COUNTCOUNT = 1;
	COUNTTIME = 1;
	LEVEL = 1;

	//Build VectorObs
	for (int i = 0; i < SizeVO; i++)
	{
		VectorObs[i].ResetDefault({ Random(-100,2000),Random(1700,3000) });
	}
	for (int i = 0; i < SizeVOM; i++)
	{
		VectorObsMove[i].ResetDefault({ Random(-100,2000),Random(1700,3000) });
	}
	//Build Character
	(*character).ResetDefault();
	//Build Boss
	boss.ResetDefault();
	//Build Boss Rambo
	bossrambo.ResetDefault();
	//Build Mini
	mini.DestroyObjectCollect();
	mini.SetObjectCollect("Img/Mini.png", { 1400,3000,50,50 }, screen);
	//Build Big
	fast.DestroyObjectCollect();
	fast.SetObjectCollect("Img/Big.png", { 400,5000,50,50 }, screen);
	//Build Bullet
	for (auto& bullet : bullets)
	{
		bullet.SetBullet(screen);
	}
	//Build Complete
	complete->SetComplete(screen);
	//Build Shield
	shield.DestroyObjectCollect();
	shield.SetObjectCollect("Img/Shield Frame.png", { 800,2500,50,50 }, screen);
	//Build Shield Red
	shieldred.DestroyObjectCollect();
	shieldred.SetObjectCollect("Img/Shield Red Frame.png", { 800,3000,50,50 }, screen);	
	//Build Blade
	for (auto& blade : blades)
	{
		blade.ResetDefault();
	}
	//Reset Fire Area
	fire.ResetDefault();
}
void Game::CountTime(SDL_Renderer* screen)
{
	//Set Count
	if(COUNT>=0)
		fontcount = TTF_OpenFont("Font/Techno.ttf", 80);
	int x_count = SCREEN_WIDTH / 2, y_count = SCREEN_HEIGHT / 2-100;
	if (COUNT == 3)
	{
		SDL_DestroyTexture(texcount);
		SDL_Surface* surfacecount = TTF_RenderText_Solid(fontcount, "3", { 73,71,71,255 });
		rectcount = { x_count,y_count,surfacecount->w,surfacecount->h };
		texcount = SDL_CreateTextureFromSurface(screen, surfacecount);
		SDL_FreeSurface(surfacecount);
		TTF_CloseFont(fontcount);
	}
	if (COUNT == 2)
	{
		SDL_DestroyTexture(texcount);
		SDL_Surface* surfacecount = TTF_RenderText_Solid(fontcount, "2", { 73,71,71,255 });
		rectcount = { x_count,y_count,surfacecount->w,surfacecount->h };
		texcount = SDL_CreateTextureFromSurface(screen, surfacecount);
		SDL_FreeSurface(surfacecount);
		TTF_CloseFont(fontcount);
	}
	if (COUNT == 1)
	{
		SDL_DestroyTexture(texcount);
		SDL_Surface* surfacecount = TTF_RenderText_Solid(fontcount, "1", { 73,71,71,255 });
		rectcount = { x_count,y_count,surfacecount->w,surfacecount->h };
		texcount = SDL_CreateTextureFromSurface(screen, surfacecount);
		SDL_FreeSurface(surfacecount);
		TTF_CloseFont(fontcount);
	}
	if (COUNT == 0)
	{
		SDL_DestroyTexture(texcount);
		SDL_Surface* surfacecount = TTF_RenderText_Solid(fontcount, "GO !", { 140,255,78,255 });
		rectcount = { x_count-50,y_count,surfacecount->w,surfacecount->h };
		texcount = SDL_CreateTextureFromSurface(screen, surfacecount);
		SDL_FreeSurface(surfacecount);
		TTF_CloseFont(fontcount);
	}
	if (COUNT >= 0)
	{
		SDL_RenderCopy(screen, texcount, NULL, &rectcount);
		if (COUNTCOUNT % 55 == 0)
		{
			if(!PAUSE)
				COUNT--;
			COUNTCOUNT = 0;
		}
		if(!PAUSE)
		COUNTCOUNT++;
	}
}
void Game::RunGame(SDL_Renderer* screen, Mouse& mouse,bool& check,const int & charactertype,Sound &sound,Settings &settings,std::string &bestscore, std::string& bestspeed)
{
	backgroundmusic.Play();
	while (RUN)
	{
		backgroundmusic.volumn = sound.volumn;
		backgroundmusic.AdjustVolumn();
		if (PAUSE)
			backgroundmusic.Pause();
		else
			backgroundmusic.Resume();
		if (complete->again.IsSelected)
		{
			complete->DestroyComplete();
			ResetGame(screen,charactertype);
			PLAY = true;
			complete->again.IsSelected = false;
			complete->show = false;
			PAUSE = false;
			backgroundmusic.Play();
		}
		mouse.UpdateMouse();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				RUN=false;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					PAUSE = !PAUSE;
				}
				if(!PAUSE)
					(*character).ControlCharacter(event, (*character).speed,screen,PLAY,PAUSE);
				settings.UpdateAll(screen, event, mouse, sound);
			}
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				(*complete).CheckActive(event);
				if(!settingbutton.IsPoint)
					homebutton.CheckActive(event);
				if (!homebutton.IsPoint)
				settingbutton.CheckActive(event);
				if(settings.RUN)
				{
					settings.exitbutton.CheckActive(event);
					settings.speakerbutton.CheckActive(event);
					settings.mutebutton.CheckActive(event);
				}
			}
			if (event.type == SDL_MOUSEWHEEL)
			{
				if (settings.RUN)
				{
					settings.AdjustVolumn(screen, event, mouse, sound);
				}
			}
		}
		//Update Information
		if(PLAY && !PAUSE)
		{
			METERCOUNT++;
			SPEEDCOUNT++;
		}
		else if(!PLAY)
		{
			COUNTTIME++;
			if(COUNTTIME%100==0)
			{
				complete->show = true;
				COUNTTIME = 0;
			}
		}
		if ((*character).speed!=0 && LEVEL<5 && PLAY && !PAUSE && !(*character).fast)
		{
			if (character->speed >=1)
				LEVEL = 1;
			if (character->speed >= 4)
				LEVEL = 2;
			if (character->speed >= 8)
				LEVEL = 3;
			if (character->speed >= 12)
				LEVEL = 4;
			if (character->speed >= 16)
				LEVEL = 5;
		}
		SDL_RenderClear(screen);
		if (fire.RUN)
		{

			texinfo = LoadIMG(screen, "Img/Infomation Fire.png");
			backgroundfire.RenderCopy(screen, NULL);
			fire.RenderCopy(screen);
			if(!PAUSE)
			{
				fire.CheckDanger((*character), PLAY);
				fire.Minimum();
			}
			SDL_RenderCopy(screen, texinfo, NULL, &rectinfo);
			SDL_DestroyTexture(texinfo);
		}
		else
		{
			texinfo = LoadIMG(screen, "Img/Infomation.png");
			background.RenderCopy(screen, NULL);
			SDL_RenderCopy(screen, texinfo, NULL, &rectinfo);
			SDL_DestroyTexture(texinfo);
		}
		(*character).RenderCopy(screen,PLAY);
		if(!PAUSE)
		{
			character->UpdateInfo(screen, METERCOUNT, SPEEDCOUNT, PLAY);
			complete->UpdateComplete(screen, (*character), METERCOUNT, sound);
		}
		if(!PAUSE)
		{
			shieldred.AnimationObject((*character).speed, PLAY);
			shield.AnimationObject((*character).speed, PLAY);
			mini.AnimationObject((*character).speed, PLAY);
			fast.AnimationObject((*character).speed, PLAY);
			bossrambo.AnimationBossRambo(PLAY);
			bossrambo.BossShot((*character), bullets, PLAY);
			boss.BossCatch((*character), PLAY);
		}
		shield.CollectObject((*character),"blue", PLAY);
		shield.RenderCopy(screen);
		shieldred.CollectObject((*character),"red",PLAY);
		shieldred.RenderCopy(screen);
		mini.CollectObject((*character), "mini", PLAY);
		mini.RenderCopy(screen);
		fast.CollectObject((*character), "fast", PLAY);
		fast.RenderCopy(screen);
		bossrambo.RenderCopy(screen,bullets,PLAY,PAUSE);
		boss.RenderCopy(screen,PLAY,PAUSE);
		if(LEVEL<=5)
		switch (LEVEL)
		{
		case 1:
			SizeVO = 5;
			break;
		case 2:
			SizeBlade = 1;
			SizeVO = 10;
			break;
		case 3:
			if (!change)
			{
				fire.RUN = 1;
				change = true;
			}
			SizeBlade = 3;
			SizeVO = 20;	
			break;
		case 4:
			SizeBlade = 4;
			SizeVO = 30;
			for (int i = 0; i < 30; i++)
			{
				VectorObs[i].ImpactObject((*character), (*character).speed, (*character).shield, PLAY);
				if (!PAUSE)
					VectorObs[i].AnimationObject((*character).speed, VectorObs, PLAY);
				VectorObs[i].RenderCopy(screen);
			}
			break;
		case 5:
			SizeBlade = 6;
			SizeVO = 40;
		}
		//Blades
		for (int i = 0; i < SizeBlade; i++)
		{
			if (!PAUSE && PLAY)
			{
				blades[i].ImpactBlade((*character), PLAY, (*character).shield);
				blades[i].AnimationBlade((*character).speed);
			}
			blades[i].RenderCopy(screen);
		}
		//Obstacle Move
		for (int i = 0; i <SizeVOM; i++)
		{
			if (!PAUSE && PLAY)
			{
				VectorObsMove[i].AnimationObject((*character).speed, VectorObs, PLAY);
				VectorObsMove[i].ImpactObject((*character), (*character).speed, (*character).shield, PLAY);
			}
			VectorObsMove[i].MoveObject();
			VectorObsMove[i].RenderCopy(screen);
		}
		//Obstacle
		for (int i = 0; i <SizeVO; i++)
		{
			if (!PAUSE && PLAY)
			{
				VectorObs[i].AnimationObject((*character).speed, VectorObs, PLAY);
				VectorObs[i].ImpactObject((*character), (*character).speed, (*character).shield, PLAY);
			}
			VectorObs[i].RenderCopy(screen);
		}
		//Pause
		if (PAUSE)
		{
			SDL_Rect* currentpauseframe = &rectpauseframe[countframepause];
			SDL_RenderCopy(screen, texpause, currentpauseframe, &rectpause);
			fpsframepause++;
			if (fpsframepause % 50 == 0)
			{
				countframepause++;
				fpsframepause = 1;
				if (countframepause == 2)
					countframepause = 0;
			}
		}
		CountTime(screen);
		if (homebutton.IsSelected)
		{
			//DestroyGame();
			backgroundmusic.Pause();
			complete->show = false;
			RUN = false;
			check = false;
		}
		int m = std::stoi(bestscore.substr(0, bestscore.find("km"))) * 1000 + std::stoi(bestscore.substr(bestscore.find("km") + 2, bestscore.find("m")));
		if (complete->show)
		{
			int m = std::stoi(bestscore.substr(0, bestscore.find("km")))*1000+std::stoi(bestscore.substr(bestscore.find("km")+2, bestscore.find("m")));
			if(m< (*character).meter*1000+METERCOUNT)
			{
				bestscore = to_string((*character).meter) + "km" + to_string(METERCOUNT) + "m";
				bestspeed = to_string((*character).speed) + "mph";
				std::fstream file_output;
				file_output.open("Input.INP");
				file_output << bestscore;
				file_output << std::endl << bestspeed;
				file_output.close();
			}
			backgroundmusic.Stop();
			complete->gameoversound.volumn = backgroundmusic.volumn;
			complete->gameoversound.AdjustVolumn();
			complete->RenderCopy(screen, mouse, bestscore);
		}
		settings.RenderCopy(screen, mouse);
		settings.UpdateAll(screen, event, mouse, sound);
		homebutton.RenderCopy(screen);
		homebutton.UpdateButton(mouse);
		settingbutton.RenderCopy(screen);
		settingbutton.UpdateButton(mouse);
		if (settingbutton.IsSelected )
		{
			settings.RUN = true;
			settingbutton.IsSelected = false;
		}
		mouse.RenderCopy(screen);
		SDL_RenderPresent(screen);
	}
}
void Game::DestroyGame()
{
	VectorObs.clear();
	VectorObsMove.clear();
	blades.clear();
	bullets.clear();
	for (auto& bullet : bullets)
	{
		bullet.DestroyBullet();
	}
	delete character;
	complete->DestroyComplete();
	boss.DestroyBoss();
	bossrambo.DestroyBossRambo();
	shield.DestroyObjectCollect();
	shieldred.DestroyObjectCollect();
	homebutton.DestroyButton();
	SDL_DestroyTexture(texcount);
}