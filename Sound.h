#ifndef SOUND_H
#define SOUND_H

#include"Function.h"

class Sound
{
private:
	Mix_Chunk* sound = NULL;
	Mix_Music* music = NULL;
	bool IsChunk=false;
	int channel;
public:
	Sound();
	~Sound();
	int volumn = MIX_MAX_VOLUME/2;
	void SetSound(std::string path, int CHANNEL, bool soundeffect);
	void DestroySound();
	void AdjustVolumn();
	void Play();
	void Pause();
	void Resume();
	void Stop();
};

#endif
