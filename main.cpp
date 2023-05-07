#include"Function.h"
#include"Background.h"
#include"Character.h"
#include"Game.h"
#include"Object.h"
#include"Boss.h"
#include"Complete.h"
#include"Home.h"
#include"Widgets.h"
using namespace std;
//Declare
Uint32 elap = 0;
Home home;
bool InitData()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError();
		return false;
	}
	if (TTF_Init() < 0)
	{
		std::cout << SDL_GetError();
		return false;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << SDL_GetError();
		return false;
	}
	Mix_Init(MIX_INIT_MP3);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow("Run With Ghost", 
												SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED,
												SCREEN_WIDTH, 
												SCREEN_HEIGHT, 
												SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL );
	if (window == NULL)
	{
		return false;
	}
	else
	{
		screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (screen == NULL)
			return false;
		else
		{
			SDL_SetRenderDrawColor(screen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false;
			}
		}
	}
	return success;
}
void close()
{
	SDL_DestroyRenderer(screen);
	screen = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
}
void SetAll()
{
	SDL_Surface* icon = IMG_Load("Img/Logo.png");
	SDL_SetWindowIcon(window,icon);
}

int main(int argc, char* argv[])
{
	if (InitData() == false)
	{
		cout<<"Init Error";
	}
	SetAll();
	home.RenderCopy(screen,event,window);
	close();
	return 0;
}