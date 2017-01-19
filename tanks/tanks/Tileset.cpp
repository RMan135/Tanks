#include "Tileset.h"
#include <cstring>

void Tileset::loadTileset(char theme[])
{
	char path[256] = "media/";
	char aux[256];
	strcpy_s(aux, path);
	strcat_s(aux, theme);
	strcpy_s(path, aux);
	strcat_s(path, "_wall.png");
	wall.loadTexture(path);
	strcpy_s(path, aux);
	strcat_s(path, "_ground.png");
	ground.loadTexture(path);
}