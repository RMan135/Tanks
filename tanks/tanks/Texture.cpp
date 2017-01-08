#include "Texture.h"
#include <iostream>
#include <SDL.h>
using namespace std;
Texture::Texture()
{
	texture = NULL;
	renderTarget = NULL;
	width = 0;
	height = 0;
	loaded = false;
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
	bool success = true;
	SDL_Surface *image = IMG_Load(path);
	if (image == NULL)
	{
		cout << "Could not load image from " << path << " ! " << SDL_GetError() << endl;
		success = false;
	}
	texture = SDL_CreateTextureFromSurface(renderTarget, image);
	if(texture == NULL)
	{
		cout << "Could not convert image from " << path << " ! " << SDL_GetError() << endl;
		success = false;
	}
	
	if (success)
	{
		loaded = true;
		width = image->w;
		height = image->h;
	}
}

void Texture::simpleRender(int x, int y, double scale)
{
	if (!loaded)
	{
		cout << "Textrue has not been loaded yet!" << endl;
	}
	else
	{
		SDL_Rect renderSpace = { x, y, width*scale, height*scale };
		SDL_RenderCopy(renderTarget, texture, NULL, &renderSpace);
	}
}

void Texture::render(int x, int y, double angle, double scale, SDL_Rect* clip, SDL_RendererFlip flip, SDL_Point* center)
{
	SDL_Rect renderSpace = { x, y, width*scale, height*scale };
	if (clip != NULL)
	{
		renderSpace.w = clip->w;
		renderSpace.h = clip->h;
	}
	SDL_RenderCopyEx(renderTarget, texture, clip, &renderSpace, angle, center, flip);
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
}