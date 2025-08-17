#include "ActiveTetromino.h"

ActiveTetromino::ActiveTetromino(const Tetromino& other):
	Tetromino(other),
	Placeholder(other)
{
	Movement.Completed = std::bind_front(&ActiveTetromino::OnActiveTetrominoActionCompleted, this);
	Placeholder.SetBackground(PlaceholderColor);
}

void ActiveTetromino::Render(SDL_Renderer* renderer) const
{
	Placeholder.Render(renderer);
	Tetromino::Render(renderer);
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
	NeedsToFall = false;

	return *this;
}

void ActiveTetromino::OnActiveTetrominoActionCompleted(Action* sender, 
													   const ActionEventArgs& e)
{
	Move(MovementSide::Down);
}
