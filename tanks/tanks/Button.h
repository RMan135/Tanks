#pragma once
#include "Texture.h"

class Button
{
private:

	int x, y, width, height;
	Texture texture;
	bool active;
	bool visible;
	char name[16];
	char job[16];
	int jobAux;

public:
	Button(int buttonX = 0, int buttonY = 0, int buttonWidth = 0, int buttonHeight = 0);

	void setActive();

	void setInactive();

	bool isActive();

	void hide();

	void unhide();

	bool pointIsInside(int pointX, int pointY);

	void setRenderTarget(SDL_Renderer *target);

	void loadTexture(char path[], bool resize = 1);

	void show();

	void centerHorizontal(int screenWidth);

	void centerVertical(int screenHeight);

	void center(int screenWidth, int screenHeight);

	void setName(char n[16]);

	char *getName();

	void setJob(char j[16]);

	char *getJob();

	bool isJob(char j[]);

	void setJobAux(int jAux);

	int getJobAux();
};

