#pragma once
#include "Button.h"

class Menu
{
private:

	int buttonNumber;
	Button buttons[16];
	SDL_Renderer *renderTarget;

public:

	Menu();

	void setRenderTarget(SDL_Renderer *target);

	void addButton(int x, int y, char path[], char name[16], char job[16], int jobAux = 0);

	void loadMenu(char name[16]);

	Button *getButtons();

	int getNumberOfButtons();

	void show();
};

