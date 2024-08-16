#include "ActiveTetromino.h"

ActiveTetromino::ActiveTetromino(TetrominoType type,
								 const std::array<Cell, 4>& cells) noexcept:
	Tetromino(type, cells),
	PlaceHolder(type, cells)
{
	BindMovement();
	PlaceHolder.SetBackground(PlaceHolderColor);
}

ActiveTetromino::ActiveTetromino(const Tetromino& other):
	Tetromino(other),
	PlaceHolder(other)
{
	BindMovement();
	PlaceHolder.SetBackground(PlaceHolderColor);
}

void ActiveTetromino::UpdatePlaceHolder()
{
	PlaceHolder.CopyCoordinates(*this);
}

Tetromino& ActiveTetromino::operator=(const Tetromino& other) noexcept
{
	_cells = other.GetCells();
	_type = other.GetType();
	PlaceHolder = other;
	PlaceHolder.SetBackground(PlaceHolderColor);

	return *this;
}

void ActiveTetromino::OnActiveTetrominoActionCompleted(Action* sender, 
													   const ActionEventArgs& e)
{
	Move(MovementSide::Down);
}

void ActiveTetromino::BindMovement()
{
	using namespace std::placeholders;

	Movement.ActionCompleted =
		std::bind(&ActiveTetromino::OnActiveTetrominoActionCompleted, this, _1, _2);
}
