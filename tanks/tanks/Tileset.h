#pragma once
#include "Texture.h"

extern SDL_Renderer *RENDER_TARGET;

struct Tileset
{
	Texture wall;
	Texture ground;

	void loadTileset(char theme[]);
};