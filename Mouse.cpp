#include"Mouse.h"
#include"Function.h"
Mouse::Mouse()
{
	rect.w = 25;
	rect.h = 25;
	point.w = 1;
	point.h = 1;
}
Mouse::~Mouse()
{
	SDL_DestroyTexture(tex);

}
void Mouse::UpdateMouse()
{
	SDL_GetMouseState(&rect.x, &rect.y);
	point.x = rect.x;
	point.y = rect.y;
}
void Mouse::RenderCopy(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, tex, NULL, &rect);
}
void Mouse::SetMouse(SDL_Renderer* screen)
{
	tex = LoadIMG(screen, "Img/Mouse Cursor.png");
	SDL_ShowCursor(SDL_DISABLE);
	if (!tex)
	{
		std::cout << SDL_GetError();
	}
}
void Mouse::DestroyMouse()
{
	tex = NULL;
	SDL_DestroyTexture(tex);
}