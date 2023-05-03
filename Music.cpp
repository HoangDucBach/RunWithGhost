#include"Music.h"

Music::Music()
{}
Music::~Music()
{}
void Music::SetMusic(std::string path)
{
	music = Mix_LoadMUS(path.c_str());
}
void Music::PlayMusic()
{
	Mix_PlayMusic(music,-1);
}
void Music::PauseMusic()
{
	Mix_PauseMusic();
}
void Music::DestroyMusic()
{
	Mix_FreeMusic(music);
}
