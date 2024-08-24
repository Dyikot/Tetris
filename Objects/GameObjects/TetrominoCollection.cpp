#include "TetrominoCollection.h"


TetrominoCollection::TetrominoCollection(Texture& cellTexture) noexcept:
	std::array<Tetromino, 7>(
		{
			Tetromino(TetrominoType::I,
					  std::array<Cell, 4>
					  {
						  Cell(cellTexture, SDL_Point{.x = 30, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 40, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 60, .y = 0 })
					  }),
			Tetromino(TetrominoType::J,
					  std::array<Cell, 4>
					  {
						  Cell(cellTexture, SDL_Point{.x = 40, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 40, .y = 10 }),
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 10 }),
						  Cell(cellTexture, SDL_Point{.x = 60, .y = 10 })
					  }),
			Tetromino(TetrominoType::L,
					  std::array<Cell, 4>
					  {
						  Cell(cellTexture, SDL_Point{.x = 60, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 60, .y = 10 }),
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 10 }),
						  Cell(cellTexture, SDL_Point{.x = 40, .y = 10 })
					  }),
			Tetromino(TetrominoType::O,
					  std::array<Cell, 4>
					  {
						  Cell(cellTexture, SDL_Point{.x = 40, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 40, .y = 10 }),
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 10 })
					  }),
			Tetromino(TetrominoType::S,
					  std::array<Cell, 4>
					  {
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 60, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 40, .y = 10 }),
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 10 })
					  }),
			Tetromino(TetrominoType::T,
					  std::array<Cell, 4>
					  {
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 40, .y = 10 }),
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 10 }),
						  Cell(cellTexture, SDL_Point{.x = 60, .y = 10 })
					  }),
			Tetromino(TetrominoType::Z,
					  std::array<Cell, 4>
					  {
						  Cell(cellTexture, SDL_Point{.x = 40, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
						  Cell(cellTexture, SDL_Point{.x = 50, .y = 10 }),
						  Cell(cellTexture, SDL_Point{.x = 60, .y = 10 })
					  })
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
