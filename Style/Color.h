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
	Grey,
	Whitesmoke,
	Lightgreen,
	Darkgrey
};

class Colors
{
public:
	static constexpr int Count = 14;
	static constexpr SDL_Color None = SDL_Color(0, 0, 0, 0);
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
		Grey,
		Whitesmoke,
		Lightgreen,
		Darkgrey
	};
public:
	static constexpr SDL_Color ToSDL_Color(Color color) noexcept;

	static void SetRenderColor(SDL_Renderer* renderer, Color color) noexcept;

	static void SetTextureColor(SDL_Texture* texture, Color color) noexcept;
};