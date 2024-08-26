#include "Tetromino.h"

Tetromino::Tetromino(Type type, Texture& cellTexture) noexcept:
	_type(type),
	_cells(CreateCellsBy(type, cellTexture))
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
	if(_type == Type::O)
	{
		return;
	}

	const auto [x, y] = GetRotationCenter(_type);
	const auto cos90 = cos(std::numbers::pi / 2);
	const auto sin90 = sin(std::numbers::pi / 2);
	SDL_Point newPosition;

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

Tetromino::Type Tetromino::GetType() const noexcept
{
	return _type;
}

std::array<Cell, 4> Tetromino::CreateCellsBy(Type type, Texture& cellTexture) const
{
	switch(type)
	{
		case Type::I:
		{
			return
			{
					Cell(cellTexture, SDL_Point{.x = 30, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 40, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 60, .y = 0 })
			};
		}
		case Type::J:
		{
			return
			{
					Cell(cellTexture, SDL_Point{.x = 40, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 40, .y = 10 }),
					Cell(cellTexture, SDL_Point{.x = 50, .y = 10 }),
					Cell(cellTexture, SDL_Point{.x = 60, .y = 10 })
			};
		}
		case Type::L:
		{
			return
			{
					Cell(cellTexture, SDL_Point{.x = 60, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 60, .y = 10 }),
					Cell(cellTexture, SDL_Point{.x = 50, .y = 10 }),
					Cell(cellTexture, SDL_Point{.x = 40, .y = 10 })
			};
		}
		case Type::O:
		{
			return
			{
					Cell(cellTexture, SDL_Point{.x = 40, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 40, .y = 10 }),
					Cell(cellTexture, SDL_Point{.x = 50, .y = 10 })
			};
		}
		case Type::S:
		{
			return
			{
					Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 60, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 40, .y = 10 }),
					Cell(cellTexture, SDL_Point{.x = 50, .y = 10 })
			};
		}
		case Type::T:
		{
			return
			{
					Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 40, .y = 10 }),
					Cell(cellTexture, SDL_Point{.x = 50, .y = 10 }),
					Cell(cellTexture, SDL_Point{.x = 60, .y = 10 })
			};
		}
		case Type::Z:
		{
			return
			{
					Cell(cellTexture, SDL_Point{.x = 40, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 50, .y = 0 }),
					Cell(cellTexture, SDL_Point{.x = 50, .y = 10 }),
					Cell(cellTexture, SDL_Point{.x = 60, .y = 10 })
			};
		}
	}
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

void Tetromino::SetBackground(const SDL_Color& background) noexcept
{
	for(auto& cell : _cells)
	{
		cell.Background = background;
	}
}

void Tetromino::CopyCoordinates(const Tetromino& tetromino) noexcept
{
	for(int i = 0; i < tetromino._cells.size(); i++)
	{
		_cells[i].Position = tetromino._cells[i].Position;
	}
}

const SDL_Point& Tetromino::GetRotationCenter(Type tetrominoType) const
{
	switch(tetrominoType)
	{
		case Type::L:
		{
			return _cells[1].Position;
		}

		case Type::I:
		case Type::J:
		case Type::S:
		case Type::T:
		case Type::Z:
		{
			return _cells[2].Position;
		}

		case Type::O:
		{
			return _cells[3].Position;
		}
	}
}
