#pragma once

#include <vector>
#include <ranges>

#include "Cell.h"
#include "Tetromino.h"
#include "../../Tools/Actions/Animation.h"

class CellStorage: public Object
{
public:
	const int Rows;
	const int Columns;
	const int ActionsForCellClearAnimation = Columns / 2;

	Texture* const CellTexture;

	Animation RowClearAnimation = Animation(/*period*/ std::chrono::milliseconds(70),
											ActionsForCellClearAnimation);
private:
	std::vector<std::vector<Cell>> _storage;

	std::vector<int> _fullRowsIndices = std::vector<int>();
public:
	CellStorage(int rows, int columns, Texture* const cellTexture) noexcept;

	void Show() const override;

	bool AreFull(int lowestRow, int highestRow);

	void ClearFullRows();

	Cell& GetCellAt(const Cell& cell);

	Cell& GetLowerCellAt(const Cell& cell);

	int GetLowerCellRow(const Cell& cell) const;

	int GetLowestRowOf(const Tetromino& tetromino) const;

	int GetHighestRowOf(const Tetromino& tetromino) const;

	bool IsLocatedAtBottom(const Cell& cell);

	bool IsLocatedAtBottom(const Tetromino& tetromino);

	void Add(const std::array<Cell, 4>& cells);

	void Add(const Tetromino& tetromino);

	const std::vector<int>& GetFullRowsIndices() const;

	std::vector<Cell>& operator[](int row);
private:
	bool IsRowFull(int row);

	void OnRowClearAnimationCompleted(Animation* sender, const AnimationEventArgs& e);

	void OnRowClearAnimationActionCompleted(Animation* sender, const AnimationEventArgs& e);
};