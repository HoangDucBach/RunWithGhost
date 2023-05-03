#include"Bullet.h"

Bullet::Bullet()
{
}
Bullet::~Bullet()
{}
void Bullet::SetBullet(SDL_Renderer* screen)
{
	this->tex = LoadIMG(screen, "Img/Bullet.png");
	this->rect.x = 0;
	this->rect.y = 50;
	this->rect.w = 10;
	this->rect.h = 10;
	this->x_float = this->rect.x;
	this->y_float = this->rect.y;
}
void Bullet::RenderCopy(SDL_Renderer* screen)
{
	SDL_RenderCopy(screen, tex, NULL, &rect);
}
void Bullet::DestroyBullet()
{
	SDL_DestroyTexture(tex);
}