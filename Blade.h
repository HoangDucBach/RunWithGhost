#ifndef BLADE_H
#define BLADE_H
#include"Function.h"
#include"Character.h"
class Blade
{
private:
	SDL_Texture* tex,*texhub;
	SDL_Rect rect,recthub;
	SDL_Rect rectframe[8];
	float x_float, y_float;
	int framecount = 0,fps=1;
	bool vertical,change = false;
public:
	void SetBlade(SDL_Renderer* screen, const bool& vertical);
	void RenderCopy(SDL_Renderer* screen);
	void AnimationBlade(const float& speed);
	void ImpactBlade(Character& character, bool& play, bool& shield);
	void ResetDefault();
};
#endif