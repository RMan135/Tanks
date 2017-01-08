#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Texture
{
private:
	SDL_Texture *texture;
	SDL_Renderer *renderTarget;
	int width, height;

public:

	Texture();

	~Texture();

	void setRenderTarget(SDL_Renderer *newRenderTarget);

	void loadTexture(char path[]);

	void simpleRender(int x, int y, double scale = 1);
};

