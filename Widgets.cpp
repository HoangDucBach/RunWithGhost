#include"Widgets.h"
//Sound
//
//
Sound::Sound() {}
Sound::~Sound()
{
	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);
}
void Sound::SetSound(std::string path, int CHANNEL, bool soundeffect)
{
	channel = CHANNEL;
	IsChunk = soundeffect;
	if (soundeffect)
	{
		sound = Mix_LoadWAV(path.c_str());
	}
	else
	{
		music = Mix_LoadMUS(path.c_str());
		if (!Mix_LoadMUS(path.c_str()))
			std::cout << SDL_GetError();
	}
}
void Sound::Play()
{
	if (IsChunk)
		Mix_PlayChannel(channel, sound, -1);
	else
		Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(volumn);
	Mix_VolumeChunk(sound, volumn);
}
void Sound::Pause()
{
	if (IsChunk)
		Mix_Pause(-1);
	else
		Mix_PauseMusic();
}
void Sound::Resume()
{
	if (IsChunk)
		Mix_Resume(-1);
	else
		Mix_ResumeMusic();
}
void Sound::Stop()
{
	Mix_HaltChannel(channel);
}
void Sound::AdjustVolumn()
{
	Mix_VolumeMusic(volumn);
	Mix_VolumeChunk(sound, volumn);
}
//Button
//
//
void Button::SetButton(std::string path1, std::string path2, SDL_Renderer* screen, const SDL_Rect& rect_, const SDL_Rect& rectreplace_)
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
	if (SDL_IntersectRect(&temp, &rect, &check))
	{
		if (check.w * check.h > 100)
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
		if (IsSelected == false && temp)
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
	if (!IsPoint)
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
//Mouse 
//
//
Mouse::Mouse()
{
	rect.w = 25;
	rect.h = 25;
	point.w = 1;
	point.h = 1;
}
Mouse::~Mouse()
{
	SDL_DestroyTexture(tex);

}
void Mouse::UpdateMouse()
{
	SDL_GetMouseState(&rect.x, &rect.y);
	point.x = rect.x;
	point.y = rect.y;
}
void Mouse::RenderCopy(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, tex, NULL, &rect);
}
void Mouse::SetMouse(SDL_Renderer* screen)
{
	tex = LoadIMG(screen, "Img/Mouse Cursor.png");
	SDL_ShowCursor(SDL_DISABLE);
	if (!tex)
	{
		std::cout << SDL_GetError();
	}
}
void Mouse::DestroyMouse()
{
	tex = NULL;
	SDL_DestroyTexture(tex);
}