#ifndef WIDGETS_H
#define WIDGETS_H

#include"Function.h"
class Sound
{
private:
	Mix_Chunk* sound = NULL;
	Mix_Music* music = NULL;
	bool IsChunk = false;
	int channel;
public:
	Sound();
	~Sound();
	int volumn = MIX_MAX_VOLUME / 2;
	void SetSound(std::string path, int CHANNEL, bool soundeffect);
	void DestroySound();
	void AdjustVolumn();
	void Play();
	void Pause();
	void Resume();
	void Stop();
};
class Mouse 
{
public:
	SDL_Texture* tex = NULL;
	SDL_Rect rect;
	SDL_Rect point;
	Mouse();
	~Mouse();
	void SetMouse(SDL_Renderer* screen);
	void UpdateMouse();
	void RenderCopy(SDL_Renderer* screen);
	void DestroyMouse();

};
class Button
{
public:
	SDL_Texture* tex = NULL, * texreplace = NULL;
	SDL_Rect rect, rectreplace;
	bool IsSelected = false;
	bool IsPoint = false;
	void SetButton(std::string path1, std::string path2, SDL_Renderer* screen, const SDL_Rect& rect_, const SDL_Rect& rectreplace_);
	void UpdateButton(Mouse& mouse);
	void RenderCopy(SDL_Renderer* screen);
	void CheckActive(SDL_Event& event);
	void DestroyButton();
};
#endif // !WIDGETS_H

