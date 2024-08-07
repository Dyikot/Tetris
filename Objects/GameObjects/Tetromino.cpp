#include "Tetromino.h"

Tetromino::Tetromino(TetrominoType type, const std::array<Cell, 4>& cellStartPoints) noexcept:
	_type(type),
	_cells(cellStartPoints)
{

}

void Tetromino::Show() noexcept
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
	int shiftByY = _cells[rotationCenterIndex].StartPoint.y;
	int shiftByX = _cells[rotationCenterIndex].StartPoint.x;

	for(auto& cell : _cells)
	{
		newCoordinates.x = static_cast<int>((cell.StartPoint.x - shiftByX) * cos(angle))
						   - static_cast<int>((cell.StartPoint.y - shiftByY) * sin(angle))
						   + shiftByX;
		newCoordinates.y = static_cast<int>((cell.StartPoint.x - shiftByX) * sin(angle))
						   + static_cast<int>((cell.StartPoint.y - shiftByY) * cos(angle))
						   + shiftByY;
		cell.StartPoint = newCoordinates;
	}
}

bool Tetromino::IsOutRightBorder(int right) const noexcept
{
	return std::ranges::any_of(_cells, [right](const Cell& cell) noexcept
	{
		return cell.StartPoint.x + Cell::Size >= right;
	});
}


bool Tetromino::IsOutLeftBorder(int left) const noexcept
{
	return std::ranges::any_of(_cells, [left](const auto& cell) noexcept
	{
		return cell.StartPoint.x <= left;
	});
}

void Tetromino::CorrectCoordinates(int left, int right, int top)
{
	for(int i = 0; i < _cells.size(); i++)
	{
		if(_cells[i].StartPoint.x <= left)
		{
			for(int j = i; j < _cells.size(); j++)
			{
				if(_cells[j].StartPoint.x <= left)
				{
					Move(MovementSide::Right);
					j--;
				}				
			}
		}
		else if(_cells[i].StartPoint.x >= right)
		{
			for(int j = i; j < _cells.size(); j++)
			{
				if(_cells[i].StartPoint.x >= right)
				{
					Move(MovementSide::Left);
					j--;
				}
			}
		}
		else if(_cells[i].StartPoint.y <= top)
		{
			for(int j = i; j < _cells.size(); j++)
			{
				if(_cells[i].StartPoint.y <= top)
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

const Cell& Tetromino::GetLowestCell() const noexcept
{
	return std::ranges::max_element(_cells, [](const Cell& left, const Cell& right) noexcept
	{
		return left.StartPoint.y < right.StartPoint.y;
	}).operator*();
}

const Cell& Tetromino::GetHighestCell() const noexcept
{
	return std::ranges::max_element(_cells, [](const Cell& left, const Cell& right) noexcept
	{
		return left.StartPoint.y > right.StartPoint.y;
	}).operator*();
}

void Tetromino::SetBackground(Color background) noexcept
{
	_backgroud = background;
	for(auto& cell : _cells)
	{
		cell.SetBackground(background);
	}
}

void Tetromino::CopyCoordinates(const Tetromino& tetromino) noexcept
{
	for(int i = 0; i < tetromino._cells.size(); i++)
	{
		_cells[i].StartPoint = tetromino._cells[i].StartPoint;
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
