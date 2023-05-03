#include"Function.h"
#include"Sound.h"

Sound::Sound(){}
Sound::~Sound()
{
	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);
}
void Sound::SetSound(std::string path, int CHANNEL, bool soundeffect )
{
	channel = CHANNEL;
	IsChunk = soundeffect;
	if (soundeffect)
	{
		sound=Mix_LoadWAV(path.c_str());
	}
	else
	{
		music=Mix_LoadMUS(path.c_str());
		if (!Mix_LoadMUS(path.c_str()))
			std::cout << SDL_GetError();
	}
}
void Sound::Play()
{
	if (IsChunk)
		Mix_PlayChannel(channel,sound,-1);
	else
		Mix_PlayMusic(music,-1);
	Mix_VolumeMusic(volumn);
	Mix_VolumeChunk(sound, volumn);
}
void Sound::Pause()
{
	if(IsChunk)
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