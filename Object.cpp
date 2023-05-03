#include"Object.h"

int fpsframe = 0;
// Class Object
Object::Object(const SDL_Rect &rect) 
{
	this->rect = rect;
	this->x_float = rect.x;
	this->y_float = rect.y;
	this->speed = rect.x;
	this->x_right= rect.x+rect.w/2;
	this->x_left = rect.x;
	this->speed_ = (float)Random(1,5)/4;
	this->xfloat_ = this->x_left;
}
Object::~Object() {}
void Object::SetObject(std::string path,SDL_Renderer* screen)
{
	tex = LoadIMG(screen, path.c_str());
	if (path == "Img/Obs 4.png" || path == "Img/Obs 5.png")
	{
		mini = true;
	}
}
SDL_Rect Object::GetRect()
{
	return this->rect;
}
bool Object::CheckDistance(std::vector<Object> & vectorobject)
{
	for (auto x : vectorobject)
	{
		if (Distance(rect, x.GetRect()) < 1000 && Distance(rect, x.GetRect()) !=0)
			return false;
	}
	return true;
}
void Object::RenderCopy(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, tex, NULL, &rect);
}
void Object::AnimationObject(const float& speed_, std::vector<Object> & vectorobject, bool& play)
{
	if(play)
	{
		y_float -= speed_;
		rect.y = int(y_float);
		rect.x = int(x_float);
		if (rect.y <= -150)
		{
			x_float = Random(-10, 2000);
			y_float = Random(1000, 2000);
			this->x_right = x_float + rect.w / 2;
			this->x_left = x_float;
			this->xfloat_ = this->x_left;
		}
	}
}
void Object::MoveObject()
{
	if (right)
	{
		xfloat_+=this->speed_;
		rect.x = (int)xfloat_;
		if (rect.x >= x_right)
		{
			right = false;
			left = true;
		}
	}
	if (left)
	{
		xfloat_ -= this->speed_;
		rect.x = (int)xfloat_;
		if (rect.x <= x_left)
		{
			right = true;
			left = false;
		}
	}

}
void Object::ImpactObject(Character& character,int &speed,bool& shield ,bool& play)
{
	SDL_Rect temp = character.GetRect();
	SDL_Rect check;
	if(play && !shield)
	{
		if ((temp.x+temp.w/2) >= rect.x && temp.x <= (rect.x + rect.w) && (temp.y+temp.h )> (rect.y+1/2*rect.h) && SDL_HasIntersection(&temp,&rect))
		{
			play = false;
			character.aleft = 0;
			character.aright = 0;
		}
		//if (SDL_IntersectRect(&rect, &temp, &check) && !mini && abs(temp.x + temp.w / 2 - (rect.x + rect.w / 2)) < 30)
		//{
		//	if (check.w * check.h >= temp.w * temp.h && temp.y - rect.y >= 0.5 * rect.h)
		//	{
		//		/*speed = 0;*/
		//		play = false;
		//		character.aleft = 0;
		//		character.aright = 0;
		//	}
		//}
		//if (mini)
		//{
		//	if (SDL_IntersectRect(&rect, &temp, &check))
		//	{
		//		if (check.w * check.h > 50 && abs(temp.y - rect.y) < 20 && abs(temp.x + temp.w / 2 - (rect.x + rect.w / 2)) < 20)
		//		{
		//			/*speed = 0;*/
		//			play = false;
		//			character.aleft = 0;
		//			character.aright = 0;
		//		}
		//	}
		//}
	}
}
void Object::ResetDefault(const std::pair<int, int>& rect)
{
	this->x_float = rect.first;
	this->y_float = rect.second;
	this->speed = this->x_float;
}
void Object::DestroyObject()
{
	SDL_DestroyTexture(this->tex);
}
//
//
//
// Class ObjectCollect
ObjectCollect::~ObjectCollect(){}
void ObjectCollect::SetObjectCollect(std::string path, const SDL_Rect& rect, SDL_Renderer* screen)
{
	//Set Detail
	this->rect = rect;
	this->x_float = rect.x;
	this->y_float = rect.y;
	this->speed = rect.x;
	IsCollected = false;
	tex = LoadIMG(screen, path.c_str());
	for (int i = 0; i < 6; i++)
	{
		frame[i] = { 0,i * rect.h,rect.w,rect.h};
	}
}
void ObjectCollect::AnimationObject(const float& speed, bool& play)
{
	if (play)
	{
		y_float -= speed;
		rect.y = int(y_float);
		rect.x = int(x_float);
		if (rect.y <= -150)
		{
			x_float = Random(-10, 2000);
			y_float = Random(5000, 9000);
		}
	}
}
void ObjectCollect::CollectObject(Character& character,const std::string &color ,bool& play)
{
	SDL_Rect temp = character.GetRect();
	if (Distance(temp, rect) < 50)
	{
		IsCollected = true;
		if(color=="blue")
			character.shield = true;
		if(color=="red")
			character.shieldred = true;
		if (color == "mini")
			character.mini = true;
		if (color == "fast")
			character.fast = true;
	}
}
void ObjectCollect::RenderCopy(SDL_Renderer* screen)
{
	SDL_Rect* currentframe = &frame[framecount];
	fpsframe++;
	if (fpsframe % 7 == 0)
	{
		framecount++;
		fpsframe = 0;
	}
	if (framecount == 5)
		framecount = 0;
	SDL_RenderCopy(screen, tex, currentframe, &rect);
}
void ObjectCollect::DestroyObjectCollect()
{
	SDL_DestroyTexture(tex);
}
