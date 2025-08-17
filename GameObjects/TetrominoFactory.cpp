#include "TetrominoFactory.h"


TetrominoFactory::TetrominoFactory(Texture& cellTexture) noexcept:
	_items(
		{
			Tetromino(Tetromino::Type::I, cellTexture),
			Tetromino(Tetromino::Type::J, cellTexture),
			Tetromino(Tetromino::Type::L, cellTexture),
			Tetromino(Tetromino::Type::O, cellTexture),
			Tetromino(Tetromino::Type::S, cellTexture),
			Tetromino(Tetromino::Type::T, cellTexture),
			Tetromino(Tetromino::Type::Z, cellTexture)
		})
{}

Tetromino TetrominoFactory::Create()
{
	Random random;
	auto color = random.GetItem(TetrominoColors);
	auto tetromino = random.GetItem(_items);
	tetromino.SetBackground(color);
	
	return tetromino;
}
