#pragma once

#include "Colors.h"
#include "SDL/SDL.h"

class Color
{
public:
	static void SetRenderColor(SDL_Renderer* renderer, Colors color);

	static SDL_Color ToSDL_Color(Colors color);
};