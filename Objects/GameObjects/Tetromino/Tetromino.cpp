#include "Tetromino.h"

Tetromino::Tetromino(TetrominoType type, const std::array<Cell, 4>& cells) noexcept:
	_type(type),
	_cells(cells)
{

}

void Tetromino::Show() const noexcept
{
	for(auto& cell : _cells)
	{
		cell.Show();
	}
}

void Tetromino::Move(MovementSide movementSide) noexcept
{
	for(auto& cell : _cells)
	{
		cell.Move(movementSide);
	}
}

void Tetromino::Rotate()
{
	if(_type == TetrominoType::O)
	{
		return;
	}

	SDL_Point newPosition;

	const auto [x, y] = GetRotationCenter(_type);
	const auto cos90 = cos(std::numbers::pi / 2);
	const auto sin90 = sin(std::numbers::pi / 2);

	for(auto& cell : _cells)
	{
		newPosition.x = (cell.Position.x - x) * cos90 - (cell.Position.y - y) * sin90 + x;
		newPosition.y = (cell.Position.x - x) * sin90 + (cell.Position.y - y) * cos90 + y;
		cell.Position = newPosition;
	}
}

bool Tetromino::IsOutRightBorder(int right) const noexcept
{
	return std::ranges::any_of(_cells, [right](const Cell& cell) noexcept
	{
		return cell.Position.x + Cell::Size > right;
	});
}

bool Tetromino::IsOutTopBorder(int top) const noexcept
{
	return std::ranges::any_of(_cells, [top](const Cell& cell) noexcept
	{
		return cell.Position.y < top;
	});
}

bool Tetromino::IsOutLeftBorder(int left) const noexcept
{
	return std::ranges::any_of(_cells, [left](const auto& cell) noexcept
	{
		return cell.Position.x < left;
	});
}

void Tetromino::CorrectCoordinates(int left, int right, int top)
{
	if(IsOutLeftBorder(left))
	{
		do
		{
			Move(MovementSide::Right);
		} 
		while(IsOutLeftBorder(left));
	}
	else if(IsOutRightBorder(right))
	{
		do
		{
			Move(MovementSide::Left);
		} 
		while(IsOutRightBorder(right));
	}
	else if(IsOutTopBorder(top))
	{
		do
		{
			Move(MovementSide::Down);
		} 
		while(IsOutLeftBorder(top));
	}
}

bool Tetromino::IsOnRightBorder(int right) const noexcept
{
	return std::ranges::any_of(_cells, [right](const Cell& cell) noexcept
	{
		return cell.Position.x + Cell::Size == right;
	});
}

bool Tetromino::IsOnLeftBorder(int left) const noexcept
{
	return std::ranges::any_of(_cells, [left](const auto& cell) noexcept
	{
		return cell.Position.x == left;
	});
}

const std::array<Cell, 4>& Tetromino::GetCells() const noexcept
{
	return _cells;
}

TetrominoType Tetromino::GetType() const noexcept
{
	return _type;
}

const Cell& Tetromino::GetLowestCell() const noexcept
{
	return std::ranges::max_element(_cells, [](const Cell& left, const Cell& right) noexcept
	{
		return left.Position.y < right.Position.y;
	}).operator*();
}

const Cell& Tetromino::GetHighestCell() const noexcept
{
	return std::ranges::max_element(_cells, [](const Cell& left, const Cell& right) noexcept
	{
		return left.Position.y > right.Position.y;
	}).operator*();
}

void Tetromino::SetBackground(Color background) noexcept
{
	Object::SetBackground(background);

	for(auto& cell : _cells)
	{
		cell.SetBackground(background);
	}
}

void Tetromino::CopyCoordinates(const Tetromino& tetromino) noexcept
{
	for(int i = 0; i < tetromino._cells.size(); i++)
	{
		_cells[i].Position = tetromino._cells[i].Position;
	}
}

const SDL_Point& Tetromino::GetRotationCenter(TetrominoType tetrominoType) const
{
	switch(tetrominoType)
	{
		case TetrominoType::L:
			return _cells[1].Position;

		case TetrominoType::I:
		case TetrominoType::J:
		case TetrominoType::S:
		case TetrominoType::T:
		case TetrominoType::Z:
			return _cells[2].Position;

		case TetrominoType::O:
			return _cells[3].Position;
		
		default:
			return _cells[0].Position;
	}
}
