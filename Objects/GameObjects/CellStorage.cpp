#include "CellStorage.h"

CellStorage::CellStorage(int rows, int columns, Texture* const cellTexture) noexcept:
	Rows(rows),
	Columns(columns),
	CellTexture(cellTexture),
	_storage(std::vector<std::vector<Cell>>(rows, std::vector<Cell>(columns)))
{
	using namespace std::placeholders;

	RowClearAnimation.AnimationCompleted =
		std::bind(&CellStorage::OnRowClearAnimationCompleted, this, _1, _2);
	RowClearAnimation.ActionCompleted =
		std::bind(&CellStorage::OnRowClearAnimationActionCompleted, this, _1, _2);
}

void CellStorage::Show() const
{
	int cellsInRow = 1;

	for(int row = Rows - 1; row >= 0; row--)
	{
		// ≈сли строка пуста€, то больше тетрамино не будет и можно выйти из цикла
		if(cellsInRow == 0)
		{
			break;
		}

		cellsInRow = 0;
		// ќтображение упавший фигур
		for(int column = 0; column < Columns; column++)
		{
			if(_storage[row][column].GetBackground() != Colors::None)
			{
				_storage[row][column].Show(
					{
						.x = column * Cell::Size,
						.y = row * Cell::Size
					});
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

bool CellStorage::AreRowsFull(const Tetromino& tetromino)
{
	auto lowestRow = GetLowestRowOf(tetromino);
	auto highestRow = GetHighestRowOf(tetromino);

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
					std::vector(Columns, Cell(CellTexture)));
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
		   GetLowerCellAt(cell).GetBackground() != Colors::None;
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
		return GetCellAt(cell).GetBackground() != Colors::None;
	});
}

void CellStorage::Add(const std::array<Cell, 4>& cells)
{
	for(const auto& cell : cells)
	{
		GetCellAt(cell) = cell;
	}
}

void CellStorage::Add(const Tetromino& tetromino)
{
	Add(tetromino.GetCells());
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
		return cell.GetBackground() == Colors::None;
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
			_storage[row][column].SetBackground(Colors::None);
		}
	}
}
