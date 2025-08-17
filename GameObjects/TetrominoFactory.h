#pragma once

#include "Random.h"
#include "Tetromino.h"

class TetrominoFactory
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
private:
	std::array<Tetromino, 7> _items;
public:
	TetrominoFactory(Texture& cellTexture) noexcept;

	Tetromino Create();
};