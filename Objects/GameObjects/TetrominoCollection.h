#pragma once

#include <array>
#include "Random/Random.h"
#include "Tetromino.h"

class TetrominoCollection: public std::array<Tetromino, 7>
{
public:
	static constexpr std::array<SDL_Color, 7> TetrominoColors = 
	{
		Colors::Green,
		Colors::Blue,
		Colors::Red,
		Colors::Cyan,
		Colors::Yellow,
		Colors::Pink,
		Colors::Orange
	};
protected:
	Random _random;
public:
	TetrominoCollection(Texture& cellTexture) noexcept;

	Tetromino SelectRandom();
};