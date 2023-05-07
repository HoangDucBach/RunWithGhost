#include"Object.h"

int fpsframe = 0;
// Class Object
//
//
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
//Blade
// 
// 
void Blade::SetBlade(SDL_Renderer* screen, const bool& vertical)
{
	//Set Ver or Hoz
	this->vertical = vertical;
	//Set Detail
	this->rect.x = ((Random(0, 1)) ? 0 : 1600);
	this->rect.y = 1000;
	this->rect.w = 40;
	this->rect.h = 40;

	//Set Link
	tex = LoadIMG(screen, "Img/Blade.png");
	if (vertical)
	{
		texhub = LoadIMG(screen, "Img/Hub Vertical.png");
		this->recthub.x = Random(-1000, -100);
		this->recthub.y = 0;
		this->recthub.w = 4;
		this->recthub.h = 960;
	}
	else
	{
		texhub = LoadIMG(screen, "Img/Hub.png");
		this->recthub.x = 0;
		this->recthub.y = Random(1000, 5000);
		this->recthub.w = 1600;
		this->recthub.h = 4;
	}
	//Set Frame
	for (int i = 0; i < 8; i++)
	{
		rectframe[i] = { 0,i * 40,40,40 };
	}
}
void Blade::ImpactBlade(Character& character, bool& play, bool& shield)
{
	SDL_Rect temp = character.GetRect();
	SDL_Rect check;
	if (play && !shield)
	{
		if ((temp.x + temp.w / 2) >= rect.x && temp.x <= (rect.x + rect.w) && (temp.y + temp.h) > (rect.y + 1 / 2 * rect.h) && SDL_HasIntersection(&temp, &rect))
		{
			play = false;
			character.aleft = 0;
			character.aright = 0;
		}
	}
}
void Blade::AnimationBlade(const float& speed)
{
	if (vertical)
	{
		if (!change)
			this->rect.y -= 3;
		else
			this->rect.y += 3;
		if (this->rect.y <= 0)
			change = true;
		if (this->rect.y >= 960)
			change = false;
		x_float += speed;
		this->rect.x = (int)x_float;
		if (rect.x >= 1700)
		{
			x_float = Random(-1000, -1500);
		}
		fps++;
		this->recthub.y = 0;
		this->recthub.x = this->rect.x + this->rect.w / 2;
	}
	else
	{
		if (!change)
			this->rect.x += 3;
		else
			this->rect.x -= 3;
		if (this->rect.x >= 1700)
			change = true;
		if (this->rect.x <= 0)
			change = false;
		y_float -= speed;
		this->rect.y = (int)y_float;
		if (rect.y <= -150)
		{
			y_float = Random(1000, 5000);
		}
		fps++;
		this->recthub.x = 0;
		this->recthub.y = this->rect.y + this->rect.h / 2;
	}
}
void Blade::RenderCopy(SDL_Renderer* screen)
{
	if (fps % 1 == 0)
	{
		framecount++;
		fps = 1;
	}
	if (framecount == 7)
		framecount = 0;
	SDL_Rect* currentframe = &rectframe[framecount];
	SDL_RenderCopy(screen, texhub, NULL, &recthub);
	SDL_RenderCopy(screen, tex, currentframe, &rect);
}
void Blade::ResetDefault()
{
	//Reset Detail
	this->rect.x = 0;
	this->rect.y = 1000;
	this->rect.w = 40;
	this->rect.h = 40;

	this->x_float = this->rect.x;
	this->y_float = this->rect.y;
	if (vertical)
	{
		this->recthub.x = -100;
		this->recthub.y = 0;
		this->recthub.w = 4;
		this->recthub.h = 960;
	}
	else
	{
		this->recthub.x = 0;
		this->recthub.y = 1000;
		this->recthub.w = 1600;
		this->recthub.h = 4;
	}
}
//Fire
// 
// 
// 
void Fire::SetFire(SDL_Renderer* screen)
{
	//Set Detail
	rect.w = 1725;
	rect.h = 1725;
	rect.x = SCREEN_WIDTH / 2 - rect.w / 2;
	rect.y = SCREEN_HEIGHT / 2 - rect.h / 2;

	r = rect.w / 2;
	//Set Link
	tex = LoadIMG(screen, "Img/Fire.png");
}
void Fire::RenderCopy(SDL_Renderer* screen)
{
	if (time)
		SDL_RenderCopy(screen, tex, NULL, &rect);
}
void Fire::Minimum()
{
	if (r >= 100)
	{
		fps++;
		if (fps % 5 == 0)
		{
			rect.w -= 1;
			rect.h -= 1;
			fps = 1;
		}
	}
	else
		time--;
	r = rect.w / 2;
	if (time == 0)
		RUN = false;
	rect.x = SCREEN_WIDTH / 2 - r;
	rect.y = SCREEN_HEIGHT / 2 - r;
}
void Fire::CheckDanger(Character& character, bool& play)
{
	if (Distance(rect, character.GetRect()) > r)
		play = false;
}
void Fire::ResetDefault()
{
	//Reset Detail
	rect.w = 1725;
	rect.h = 1725;
	rect.x = SCREEN_WIDTH / 2 - rect.w / 2;
	rect.y = SCREEN_HEIGHT / 2 - rect.h / 2;

	r = rect.w / 2;
	RUN = false;
}
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
