#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Function.h"
class Background
{
private:
	SDL_Texture* tex;
	SDL_Rect rect;
public:
	Background();
	~Background();
	void LoadBackground(std::string path, SDL_Renderer* screen);
	void RenderCopy(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void FreeBackground();
};
#endif