#include "CellStorage.h"

CellStorage::CellStorage(int rows, int columns, Texture* const cellTexture) noexcept:
	Rows(rows),
	Columns(columns),
	CellTexture(cellTexture),
	_storage(std::vector<std::vector<Cell>>(rows, std::vector<Cell>(columns, Cell(*CellTexture))))
{
	using namespace std::placeholders;

	RowClearAnimation.AnimationCompleted = std::bind_front(
		&CellStorage::OnRowClearAnimationCompleted, this);
	RowClearAnimation.ActionCompleted = std::bind_front(
		&CellStorage::OnRowClearAnimationActionCompleted, this);
}

void CellStorage::Render(SDL_Renderer* renderer) const
{
	int cellsInRow = 1;

	for(int row = Rows - 1; row >= 0; row--)
	{
		// Если строка пустая, то больше тетрамино не будет и можно выйти из цикла
		if(cellsInRow == 0)
		{
			break;
		}

		cellsInRow = 0;
		// Отображение упавший фигур
		for(int column = 0; column < Columns; column++)
		{
			if(_storage[row][column].Background != Colors::Transparent)
			{
				_storage[row][column].Render(renderer, { column * Cell::Size, row * Cell::Size });
				cellsInRow++;
			}
		}
	}
}

bool CellStorage::AreRowsFull(int lowestRow, int highestRow)
{
	_fullRowsIndices.clear();

	for(int row = lowestRow; row >= highestRow; row--)
	{
		if(IsRowFull(row))
		{
			_fullRowsIndices.push_back(row);
		}
	}

	return !_fullRowsIndices.empty();
}

bool CellStorage::AreRowsFull()
{
	auto lowestRow = GetLowestRowOf(*_lastAddedTetromino);
	auto highestRow = GetHighestRowOf(*_lastAddedTetromino);

	return AreRowsFull(lowestRow, highestRow);
}

void CellStorage::ClearFullRows()
{
	if(_fullRowsIndices.empty())
	{
		return;
	}

	for(auto index : _fullRowsIndices)
	{
		_storage.erase(_storage.begin() + index);
	}
	
	_storage.insert(_storage.begin(), 
					_fullRowsIndices.size(),
					std::vector(Columns, Cell(*CellTexture)));
}

Cell& CellStorage::GetCellAt(const Cell& cell)
{
	return _storage[cell.Position.y / Cell::Size][cell.Position.x / Cell::Size];
}

Cell& CellStorage::GetLowerCellAt(const Cell& cell)
{
	return _storage[cell.Position.y / Cell::Size + 1][cell.Position.x / Cell::Size];
}

const Cell& CellStorage::GetLowerCellAt(const Cell& cell) const
{
	return _storage[cell.Position.y / Cell::Size + 1][cell.Position.x / Cell::Size];
}

int CellStorage::GetLowerCellRow(const Cell& cell) const
{
	return cell.Position.y / Cell::Size + 1;
}

int CellStorage::GetLowestRowOf(const Tetromino& tetromino) const
{
	return tetromino.GetLowestCell().Position.y / Cell::Size;
}

int CellStorage::GetHighestRowOf(const Tetromino& tetromino) const
{
	return tetromino.GetHighestCell().Position.y / Cell::Size;
}

bool CellStorage::IsLocatedAtBottom(const Cell& cell) const
{
	return GetLowerCellRow(cell) >= Rows ||
		   GetLowerCellAt(cell).Background != Colors::Transparent;
}

bool CellStorage::IsLocatedAtBottom(const Tetromino& tetromino) const
{
	return std::ranges::any_of(tetromino.GetCells(), [this](const auto& cell)
	{
		return IsLocatedAtBottom(cell);
	});
}

bool CellStorage::IsLocatedInCells(const Tetromino& tetromino)
{
	return std::ranges::any_of(tetromino.GetCells(), [this](const Cell& cell)
	{
		return GetCellAt(cell).Background != Colors::Transparent;
	});
}

void CellStorage::Add(const Tetromino& tetromino)
{
	_lastAddedTetromino = &tetromino;

	for(const auto& cell : tetromino.GetCells())
	{
		GetCellAt(cell) = cell;
	}
}

const std::vector<int>& CellStorage::GetFullRowsIndices() const
{
	return _fullRowsIndices;
}

std::vector<Cell>& CellStorage::operator[](int row)
{
	return _storage[row];
}

bool CellStorage::IsRowFull(int row)
{
	return !std::ranges::any_of(_storage[row], [](const Cell& cell)
	{
		return cell.Background == Colors::Transparent;
	});
}

void CellStorage::OnRowClearAnimationCompleted(Animation* sender, const AnimationEventArgs& e)
{
	ClearFullRows();
}

void CellStorage::OnRowClearAnimationActionCompleted(Animation* sender,
													 const AnimationEventArgs& e)
{
	const int CellToClearAmount = 2 * (e.ActionsCompleted + 1);
	const int StartColumn = Columns / 2 - e.ActionsCompleted - 1;
	const int EndColumn = Columns / 2 + e.ActionsCompleted + 1;

	for(int row : _fullRowsIndices)
	{
		for(int column = StartColumn; column < EndColumn; column++)
		{
			_storage[row][column].Background = Colors::Transparent;
		}
	}
}
