#pragma once

#include "Colors.h"

struct Style
{
	int Width;
	int Height;
	int FontSize;
	SDL_Color Background;
	SDL_Color BackgroundOnHover = Background;
	SDL_Color BorderColor;
	SDL_Color FontColor;
};