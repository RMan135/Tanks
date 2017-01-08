#pragma once
#include "Texture.h"

struct Tileset
{
	Texture wall;
	Texture ground;

	void loadTileset(char theme[], SDL_Renderer *renderTarget);
};