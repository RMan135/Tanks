#include "Tileset.h"
#include <cstring>

void Tileset::loadTileset(char theme[], SDL_Renderer *renderTarget)
{
	char path[256] = "media/";
	char aux[256];
	strcpy_s(aux, path);
	strcat_s(aux, theme);
	strcpy_s(path, aux);
	strcat_s(path, "_wall.png");
	wall.setRenderTarget(renderTarget);
	wall.loadTexture(path);
	strcpy_s(path, aux);
	strcat_s(path, "_ground.png");
	ground.setRenderTarget(renderTarget);
	ground.loadTexture(path);
}