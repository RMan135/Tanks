#include "Texture.h"

Texture::Texture()
{
	texture = NULL;
	renderTarget = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	SDL_free(texture);
	SDL_free(renderTarget);
}

void Texture::setRenderTarget(SDL_Renderer *newRenderTarget)
{
	renderTarget = newRenderTarget;
}

void Texture::loadTexture(char path[])
{
	SDL_Surface *image = IMG_Load(path);
	texture = SDL_CreateTextureFromSurface(renderTarget, image);
	width = image->w;
	height = image->h;
}

void Texture::simpleRender(int x, int y, double scale)
{
	SDL_Rect renderSpace = { x, y, width*scale, height*scale };
	SDL_RenderCopy(renderTarget, texture, NULL, &renderSpace);
}