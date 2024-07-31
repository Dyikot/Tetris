#include "Tetromino.h"

void Tetromino::Show()
{
	for(auto& cell : _cells)
	{
		cell.Show();
	}
}

void Tetromino::Move(MovementSide movementSide)
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
	Coordinates newCoordinates;
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

bool Tetromino::IsOutRightBorder(int right) const
{
	for(const auto& cell : _cells)
	{
		if(cell.StartPoint.x + Cell::Size >= right)
		{
			return true;
		}
	}
	return false;
}


bool Tetromino::IsOutLeftBorder(int left) const
{
	for(const auto& cell : _cells)
	{
		if(cell.StartPoint.x <= left)
		{
			return true;
		}
	}
	return false;
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

const std::array<Cell, 4>& Tetromino::GetCells() const
{
	return _cells;
}

const Coordinates& Tetromino::GetLowestCoordinates() const
{
	return std::ranges::max_element(_cells, [](const Cell& left, const Cell& right)
	{
		return left.StartPoint.y < right.StartPoint.y;
	}).operator*().StartPoint;
}

const Coordinates& Tetromino::GetHighestCoordinates() const
{
	return std::ranges::max_element(_cells, [](const Cell& left, const Cell& right)
	{
		return left.StartPoint.y > right.StartPoint.y;
	}).operator*().StartPoint;
}

void Tetromino::SetBackground(Color background)
{
	_backgroud = background;
	for(auto& cell : _cells)
	{
		cell.SetBackground(background);
	}
}

int Tetromino::SelectRotationCenter(TetrominoType tetrominoType) const
{
	switch(tetrominoType)
	{
		case TetrominoType::I:
			return 2;
		case TetrominoType::J:
			return 2;
		case TetrominoType::L:
			return 1;
		case TetrominoType::O:
			return 3;
		case TetrominoType::S:
			return 2;
		case TetrominoType::T:
			return 2;
		case TetrominoType::Z:
			return 2;
		default:
			throw std::exception();
	}
}
