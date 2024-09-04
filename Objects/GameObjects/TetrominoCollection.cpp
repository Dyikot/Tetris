#include "TetrominoCollection.h"


TetrominoCollection::TetrominoCollection(Texture& cellTexture) noexcept:
	std::array<Tetromino, 7>(
		{
			Tetromino(Tetromino::Type::I, cellTexture),
			Tetromino(Tetromino::Type::J, cellTexture),
			Tetromino(Tetromino::Type::L, cellTexture),
			Tetromino(Tetromino::Type::O, cellTexture),
			Tetromino(Tetromino::Type::S, cellTexture),
			Tetromino(Tetromino::Type::T, cellTexture),
			Tetromino(Tetromino::Type::Z, cellTexture)
		})
{

}

Tetromino TetrominoCollection::SelectRandom()
{
	auto color = TetrominoColors[_random.NextInt(0, 6)];
	auto tetromino = _Elems[_random.NextInt(0, 6)];
	tetromino.SetBackground(color);
	
	return tetromino;
}
