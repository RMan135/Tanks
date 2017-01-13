#pragma once
#include <SDL.h>

struct PlayerController
{
	bool fwd, bkd, left, right;
	SDL_Keycode btFwd, btBkd, btLeft, btRight;

	void keyDown(SDL_Keycode key)
	{
		if (key == btFwd)
		{
			fwd = 1;
		}
		if (key == btBkd)
		{
			bkd = 1;
		}
		if (key == btLeft)
		{
			left = 1;
		}
		if (key == btRight)
		{
			right = 1;
		}
	}

	void keyUp(SDL_Keycode key)
	{
		if (key == btFwd)
		{
			fwd = 0;
		}
		if (key == btBkd)
		{
			bkd = 0;
		}
		if (key == btLeft)
		{
			left = 0;
		}
		if (key == btRight)
		{
			right = 0;
		}
	}

	void setPlayerOne()
	{
		btFwd = SDLK_w;
		btBkd = SDLK_s;
		btLeft = SDLK_a;
		btRight = SDLK_d;
	}

	void setPlayerTwo()
	{
		btFwd = SDLK_UP;
		btBkd = SDLK_DOWN;
		btLeft = SDLK_LEFT;
		btRight = SDLK_RIGHT;
	}
};

