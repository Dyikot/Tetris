#pragma once

#include "SDL/SDL.h"
#include <array>

enum class Color
{
	None,
	Black,
	Green,
	Blue,
	Red,
	Cyan,
	Yellow,
	Pink,
	Orange,
	White,
	Grey
};

class Colors
{
public:
	static constexpr int Count = 11;
	static constexpr SDL_Color None = SDL_Color(0, 0, 0, 0);
	static constexpr SDL_Color Black = SDL_Color(0, 0, 0, 255);
	static constexpr SDL_Color Green = SDL_Color(0, 128, 0, 255);
	static constexpr SDL_Color Blue = SDL_Color(30, 144, 255, 255);
	static constexpr SDL_Color Red = SDL_Color(210, 43, 43, 255);
	static constexpr SDL_Color Cyan = SDL_Color(0, 206, 209, 255);
	static constexpr SDL_Color Yellow = SDL_Color(220, 220, 0, 255);
	static constexpr SDL_Color Pink = SDL_Color(255, 105, 180, 255);
	static constexpr SDL_Color Orange = SDL_Color(255, 140, 0, 255);
	static constexpr SDL_Color White = SDL_Color(255, 255, 255, 255);
	static constexpr SDL_Color Grey = SDL_Color(105, 105, 105, 255);
private:
	static constexpr std::array<SDL_Color, Count> _colors =
	{
		None,
		Black,
		Green,
		Blue,
		Red,
		Cyan,
		Yellow,
		Pink,
		Orange,
		White,
		Grey
	};
public:
	static constexpr SDL_Color ToSDL_Color(Color color);

	static void SetRenderColor(SDL_Renderer* renderer, Color color);

	static void SetTextureColor(SDL_Texture* texture, Color color);
};