#ifndef MUSIC_H
#define MUSIC_H

#include"Function.h"

class Music
{
public:
	Music();
	~Music();
	void SetMusic(std::string path);
	void DestroyMusic();
	void PlayMusic();
	void PauseMusic();
private:
	Mix_Music* music;
};
#endif
