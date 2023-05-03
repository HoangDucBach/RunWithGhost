#include"Background.h"
Background::Background()
{
	tex = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}
Background::~Background()
{
	FreeBackground();
}
void Background::LoadBackground(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGBA(load_surface->format, COLOR_R, COLOR_G, COLOR_B, SDL_ALPHA_TRANSPARENT));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	tex = new_texture;
}
void Background::RenderCopy(SDL_Renderer* des, const SDL_Rect* temp)
{
	SDL_Rect renderquad = { rect.x,rect.y,rect.w,rect.h };
	SDL_RenderCopy(des, tex, temp, & renderquad);
}

void Background::FreeBackground()
{	
	if (tex != NULL)
	{
		SDL_DestroyTexture(tex);
		tex = NULL;
	}
}