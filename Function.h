#ifndef FUNCTION_H
#define FUNCTION_H
//Declare include

#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<SDL.h>
#include<SDL_image.h>
#include"SDL_image.h"
#include<Windows.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<sstream>
#include<fstream>
//Global Variable

static SDL_Window* window = NULL;
static SDL_Renderer* screen = NULL;
static SDL_Event event;
//Display
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 960;
const int SCREEN_BPP = 32;
//Color
const int COLOR_R = 167;
const int COLOR_G = 175;
const int COLOR_B = 160;
//Math
const double PI = 3.141592654;
int Random(const int& min, const int& max);
float Distance(const SDL_Rect& rect1, const SDL_Rect& rect2);
SDL_Texture* LoadIMG(SDL_Renderer* screen, std::string path);
SDL_Texture* LoadFont(SDL_Renderer* screen, TTF_Font* font, std::string path,SDL_Color color);
SDL_Rect GetRectFontFromSurface(SDL_Renderer* screen, TTF_Font* font, std::string path);
std::string to_string(int number);
#endif
