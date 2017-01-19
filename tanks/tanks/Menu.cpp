#include "Menu.h"
#include <cstring>
#include <fstream>
using namespace std;
Menu::Menu()
{
	buttonNumber = 0;
}

void Menu::setRenderTarget(SDL_Renderer *target)
{
	renderTarget = target;
}

void Menu::addButton(int x, int y, char path[], char name[16], char job[16], int jobAux)
{
	buttons[buttonNumber].setX(x);
	buttons[buttonNumber].setY(y);
	buttons[buttonNumber].loadTexture(path);
	buttons[buttonNumber].setName(name);
	buttons[buttonNumber].setJob(job);
	if (jobAux != 0)
		buttons[buttonNumber].setJobAux(jobAux);
	buttonNumber++;
}

void Menu::loadMenu(char name[16])
{
	ifstream fin("menudata.txt");
	char search[32];
	do
	{
		fin.getline(search, 32);
	} while (strcmp(name, search) != 0);
	int btNum, i;
	int btX, btY, btJobAux;
	char btName[16], btJob[16], btPath[256];
	fin >> btNum;
	for (i = 0; i < btNum; i++)
	{
		fin >> btX >> btY; fin.get();
		fin.getline(btName, 16);
		fin.getline(btPath, 256);
		fin.getline(btJob, 16);
		if (strcmp(btJob, "change_state") == 0)
		{
			fin >> btJobAux;
			addButton(btX, btY, btPath, btName, btJob, btJobAux);
		}
		else
		{
			addButton(btX, btY, btPath, btName, btJob);
		}
	}
	fin.close();
}

Button* Menu::getButtons()
{
	return buttons;
}

int Menu::getNumberOfButtons()
{
	return buttonNumber;
}

void Menu::show()
{
	int i;
	for (i = 0; i < buttonNumber; i++)
	{
		buttons[i].show();
	}
}