#ifndef OBJECT_H
#define OBJECT_H

#include"Character.h"

class Object
{
private:
	SDL_Texture* tex = NULL;
	SDL_Rect rect;
	float speed;
	float x_float, y_float;
	float x_right,x_left, xfloat_;
	float speed_ = 0;
	bool left=false, right=true;
	bool mini;
public:
	Object(const SDL_Rect& rect_);
	Object(){};
	~Object();
	void SetObject(std::string path,SDL_Renderer* screen);
	SDL_Rect GetRect();
	void RenderCopy(SDL_Renderer* screen);
	void AnimationObject(const float &speed, std::vector<Object>& vectorobject, bool& play);
	bool CheckDistance(std::vector<Object>& vectorobject);
	void ImpactObject(Character& character, int& speed,bool &shield, bool& play);
	void MoveObject();
	void ResetDefault(const std::pair<int,int> & rect);
	void DestroyObject();
};
class Blade
{
private:
	SDL_Texture* tex, * texhub;
	SDL_Rect rect, recthub;
	SDL_Rect rectframe[8];
	float x_float, y_float;
	int framecount = 0, fps = 1;
	bool vertical, change = false;
public:
	void SetBlade(SDL_Renderer* screen, const bool& vertical);
	void RenderCopy(SDL_Renderer* screen);
	void AnimationBlade(const float& speed);
	void ImpactBlade(Character& character, bool& play, bool& shield);
	void ResetDefault();
};
//Fire
// 
// 
class Fire
{
private:
	SDL_Texture* tex;
	SDL_Rect rect;
	float x_float, y_float, w_float, h_float;
	float r;
	int fps = 0;
	int time = 300;
public:
	bool RUN = false;
	void SetFire(SDL_Renderer* screen);
	void RenderCopy(SDL_Renderer* screen);
	void CheckDanger(Character& character, bool& play);
	void Minimum();
	void ResetDefault();
};
//Object Collect
//
//
class ObjectCollect
{
private:
	SDL_Texture* tex = NULL;
	SDL_Rect rect;
	float speed;
	float x_float, y_float;
	SDL_Rect frame[6];
	int framecount;

public:
	~ObjectCollect();
	bool IsCollected = false;
	void SetObjectCollect(std::string path, const SDL_Rect& rect, SDL_Renderer* screen);
	void AnimationObject(const float& speed,bool& play);
	void RenderCopy(SDL_Renderer* screen);
	void CollectObject(Character& character, const std::string& color, bool& play);
	void DestroyObjectCollect();
};
#endif