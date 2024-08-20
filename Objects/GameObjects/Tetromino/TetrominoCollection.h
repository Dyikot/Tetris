#pragma once

#include <array>
#include "Random/Random.h"
#include "Tetromino.h"

class TetrominoCollection: public std::array<Tetromino, 7>
{
protected:
	Random _random;
public:
	TetrominoCollection(Texture* const cellTexture = nullptr) noexcept;

	Tetromino SelectRandom();
};