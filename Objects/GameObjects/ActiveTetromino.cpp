#include "ActiveTetromino.h"

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

void ActiveTetromino::UpdatePlaceholderPositionIn(const CellStorage& cellStorage)
{
	Placeholder.CopyCoordinates(*this);

	while(!cellStorage.IsLocatedAtBottom(Placeholder))
	{
		Placeholder.Move(MovementSide::Down);
	}
}

bool ActiveTetromino::IsLocatedAtBottomOf(const CellStorage& cellStorage)
{
	if(NeedsToFall)
	{
		NeedsToFall = false;
		CopyCoordinates(Placeholder);

		return true;
	}

	return cellStorage.IsLocatedAtBottom(*this);
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

	Movement.Completed = std::bind(&ActiveTetromino::OnActiveTetrominoActionCompleted,
								   this, _1, _2);
}