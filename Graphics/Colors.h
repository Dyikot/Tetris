#pragma once

#include "SDL/SDL.h"
#include "Random/Random.h"

class Colors
{
public:
	static constexpr SDL_Color Transparent = SDL_Color(0, 0, 0, 0);
	static constexpr SDL_Color Black = SDL_Color(20, 20, 20, 255);
	static constexpr SDL_Color Green = SDL_Color(0, 128, 0, 255);
	static constexpr SDL_Color Blue = SDL_Color(30, 144, 255, 255);
	static constexpr SDL_Color Red = SDL_Color(210, 43, 43, 255);
	static constexpr SDL_Color Cyan = SDL_Color(0, 206, 209, 255);
	static constexpr SDL_Color Yellow = SDL_Color(220, 220, 0, 255);
	static constexpr SDL_Color Pink = SDL_Color(255, 105, 180, 255);
	static constexpr SDL_Color Orange = SDL_Color(255, 140, 0, 255);
	static constexpr SDL_Color White = SDL_Color(255, 255, 255, 255);
	static constexpr SDL_Color Grey = SDL_Color(110, 110, 110, 255);
	static constexpr SDL_Color Whitesmoke = SDL_Color(230, 230, 230, 255);
	static constexpr SDL_Color Lightgreen = SDL_Color(0, 175, 0, 255);
	static constexpr SDL_Color Darkgrey = SDL_Color(70, 70, 70, 255);
};

static bool operator==(const SDL_Color& left, const SDL_Color& right)
{
	return left.r == right.r &&
		   left.g == right.g &&
		   left.b == right.b &&
		   left.a == right.a;
}

static bool operator!=(const SDL_Color& left, const SDL_Color& right)
{
	return !operator==(left, right);
}