#include "Button.h"
#include <iostream>
using namespace std;
Button::Button(int buttonX, int buttonY, int buttonWidth, int buttonHeight)
{
	x = buttonX;
	y = buttonY;
	width = buttonWidth;
	height = buttonHeight;
	active = true;
	visible = true;
	job[0] = NULL;
	jobAux = 0;
}

void Button::setActive()
{
	active = true;
	texture.setColor(255, 255, 255);
}

void Button::setInactive()
{
	active = false;
	texture.setColor(128, 128, 128);
}

bool Button::isActive()
{
	return active;
}

void Button::hide()
{
	visible = false;
}

void Button::unhide()
{
	visible = true;
}

bool Button::pointIsInside(int pointX, int pointY)
{
	if (pointX >= x && pointX <= x+width && pointY >= y && pointY <= y+height)
		return true;
	return false;
}

void Button::setRenderTarget(SDL_Renderer *target)
{
	texture.setRenderTarget(target);
}

void Button::loadTexture(char path[], bool resize)
{
	texture.loadTexture(path);
	if (resize)
	{
		width = texture.getWidth();
		height = texture.getHeight();
	}
}

void Button::show()
{
	if (visible)
	{
		SDL_Rect renderSpace = { x, y, width, height };
		SDL_RenderCopy(texture.getRenderTarget(), texture.getTexture(), NULL, &renderSpace);
	}
	else
		cout << "Trying to show invisible button!" << endl;
}

void Button::centerHorizontal(int screenWidth)
{
	int center = screenWidth / 2;
	x = center - (width / 2);
}

void Button::centerVertical(int screenHeight)
{
	int center = screenHeight / 2;
	y = center - (height / 2);
}

void Button::center(int screenWidth, int screenHeight)
{
	centerHorizontal(screenWidth);
	centerVertical(screenHeight);
}

void Button::setName(char n[64])
{
	int i = 0;
	while (n[i] != NULL)
	{
		name[i] = n[i];
		i++;
	}
	name[i] = n[i];
}

char* Button::getName()
{
	return name;
}

void Button::setJob(char j[64])
{
	int i = 0;
	while (j[i] != NULL)
	{
		job[i] = j[i];
		i++;
	}
	job[i] = j[i];
}

char* Button::getJob()
{
	return job;
}

bool Button::isJob(char j[])
{
	int i = 0;
	while (j[i] != NULL)
	{
		if (j[i] != job[i])
			return 0;
		i++;
	}
	if (j[i] != job[i])
		return 0;
	return 1;
}

void Button::setJobAux(int jAux)
{
	jobAux = jAux;
}

int Button::getJobAux()
{
	return jobAux;
}