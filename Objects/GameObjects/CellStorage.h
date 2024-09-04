#pragma once

#include <vector>
#include <ranges>

#include "Cell.h"
#include "Tetromino.h"
#include "../../Actions/Animation.h"
#include "../../Audio/GameAudioManager.h"

class CellStorage: public Object
{
public:
	const int Rows;
	const int Columns;
	Texture* const CellTexture;
	Animation RowClearAnimation = 
	{
		/*period*/ std::chrono::milliseconds(70),
		/*actions*/ static_cast<size_t>(Columns / 2)
	};
private:
	const Tetromino* _lastAddedTetromino;
	std::vector<std::vector<Cell>> _storage;
	std::vector<int> _fullRowsIndices;
public:
	CellStorage(int rows, int columns, Texture* const cellTexture) noexcept;

	void OnRender() const override;

	void ClearFullRows();

	void Add(const Tetromino& tetromino);

	bool AreRowsFull(int lowestRow, int highestRow);

	bool AreRowsFull();

	bool IsLocatedAtBottom(const Cell& cell) const;

	bool IsLocatedAtBottom(const Tetromino& tetromino) const;

	bool IsLocatedInCells(const Tetromino& tetromino);

	Cell& GetCellAt(const Cell& cell);

	Cell& GetLowerCellAt(const Cell& cell);

	const Cell& GetLowerCellAt(const Cell& cell) const;

	int GetLowerCellRow(const Cell& cell) const;

	int GetLowestRowOf(const Tetromino& tetromino) const;

	int GetHighestRowOf(const Tetromino& tetromino) const;

	const std::vector<int>& GetFullRowsIndices() const;

	std::vector<Cell>& operator[](int row);
private:
	void OnRowClearAnimationCompleted(Animation* sender, const AnimationEventArgs& e);

	void OnRowClearAnimationActionCompleted(Animation* sender, const AnimationEventArgs& e);

	bool IsRowFull(int row);
};