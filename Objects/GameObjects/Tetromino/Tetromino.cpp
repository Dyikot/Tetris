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

	auto angle = std::numbers::pi / 2;
	SDL_Point newCoordinates;
	int rotationCenterIndex = SelectRotationCenter(_type);
	int shiftByY = _cells[rotationCenterIndex].Position.y;
	int shiftByX = _cells[rotationCenterIndex].Position.x;

	for(auto& cell : _cells)
	{
		newCoordinates.x = static_cast<int>((cell.Position.x - shiftByX) * cos(angle))
						   - static_cast<int>((cell.Position.y - shiftByY) * sin(angle))
						   + shiftByX;
		newCoordinates.y = static_cast<int>((cell.Position.x - shiftByX) * sin(angle))
						   + static_cast<int>((cell.Position.y - shiftByY) * cos(angle))
						   + shiftByY;
		cell.Position = newCoordinates;
	}
}

bool Tetromino::IsOutRightBorder(int right) const noexcept
{
	return std::ranges::any_of(_cells, [right](const Cell& cell) noexcept
	{
		return cell.Position.x + Cell::Size >= right;
	});
}

bool Tetromino::IsOutLeftBorder(int left) const noexcept
{
	return std::ranges::any_of(_cells, [left](const auto& cell) noexcept
	{
		return cell.Position.x <= left;
	});
}

void Tetromino::CorrectCoordinates(int left, int right, int top)
{
	for(int i = 0; i < _cells.size(); i++)
	{
		if(_cells[i].Position.x <= left)
		{
			for(int j = i; j < _cells.size(); j++)
			{
				if(_cells[j].Position.x <= left)
				{
					Move(MovementSide::Right);
					j--;
				}				
			}
		}
		else if(_cells[i].Position.x >= right)
		{
			for(int j = i; j < _cells.size(); j++)
			{
				if(_cells[i].Position.x >= right)
				{
					Move(MovementSide::Left);
					j--;
				}
			}
		}
		else if(_cells[i].Position.y <= top)
		{
			for(int j = i; j < _cells.size(); j++)
			{
				if(_cells[i].Position.y <= top)
				{
					Move(MovementSide::Down);
					j--;
				}
			}
		}
	}
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

int Tetromino::SelectRotationCenter(TetrominoType tetrominoType) const
{
	switch(tetrominoType)
	{
		case TetrominoType::L:
			return 1;

		case TetrominoType::I:
		case TetrominoType::J:
		case TetrominoType::S:
		case TetrominoType::T:
		case TetrominoType::Z:
			return 2;	

		case TetrominoType::O:
			return 3;
		
		default:
			throw std::exception();
	}
}
