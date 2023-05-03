#include"Function.h"
#include"Background.h"
#include"Mouse.h"
#include"Button.h"
#include"Music.h"
using namespace std;
std::string to_string(int number)
{
	std::ostringstream os;
	os << number;
	if (number < 10)
		return '0' + os.str();
	else
		return os.str();
}
int Random(const int& min, const int& max)
{
	return rand() % (max - min + 1) + min;
}
float Distance(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
	return sqrt((rect1.x+rect1.w/2 - rect2.x-rect2.w/2) * (rect1.x + rect1.w / 2 - rect2.x-rect2.w/2) + (rect1.y +rect1.h/2- rect2.y-rect2.h/2) * (rect1.y + rect1.h / 2 - rect2.y - rect2.h / 2));
}
SDL_Texture* LoadIMG(SDL_Renderer* screen, std::string path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (!surface)
		std::cout << SDL_GetError();
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGBA(surface->format, COLOR_R, COLOR_G, COLOR_B, SDL_ALPHA_TRANSPARENT));
	texture = SDL_CreateTextureFromSurface(screen, surface);
	SDL_FreeSurface(surface);
	return texture;
}
SDL_Texture* LoadFont(SDL_Renderer* screen,TTF_Font *font,std::string path,SDL_Color color)
{
	SDL_Surface *surface;
	SDL_Texture* texture;
	surface = TTF_RenderText_Blended(font, path.c_str(), color);
	texture = SDL_CreateTextureFromSurface(screen, surface);
	SDL_FreeSurface(surface);
	return texture;
}
SDL_Rect GetRectFontFromSurface(SDL_Renderer* screen, TTF_Font* font, std::string path)
{
	SDL_Surface* surface;
	surface = TTF_RenderText_Blended(font, path.c_str(),{0,0,0,255});
	SDL_Rect temp;
	temp.w = surface->w;
	temp.h = surface->h;
	SDL_FreeSurface(surface);
	return temp;
}