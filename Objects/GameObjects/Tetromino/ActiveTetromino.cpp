#include "ActiveTetromino.h"

ActiveTetromino::ActiveTetromino(TetrominoType type,
								 const std::array<Cell, 4>& cells) noexcept:
	Tetromino(type, cells),
	Placeholder(type, cells)
{
	BindMovement();
	Placeholder.SetBackground(PlaceholderColor);
}

ActiveTetromino::ActiveTetromino(const Tetromino& other):
	Tetromino(other),
	Placeholder(other)
{
	BindMovement();
	Placeholder.SetBackground(PlaceholderColor);
}

void ActiveTetromino::Show() const noexcept
{
	Placeholder.Show();
	Tetromino::Show();
}

void ActiveTetromino::UpdatePlaceholderPosition()
{
	Placeholder.CopyCoordinates(*this);
}

void ActiveTetromino::MovePlaceholderAtBottomOf(const CellStorage& cellStorage)
{
	while(!cellStorage.IsLocatedAtBottom(Placeholder))
	{
		Placeholder.Move(MovementSide::Down);
	}
}

Tetromino& ActiveTetromino::operator=(const Tetromino& other) noexcept
{
	_cells = other.GetCells();
	_type = other.GetType();
	Placeholder = other;
	Placeholder.SetBackground(PlaceholderColor);

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
