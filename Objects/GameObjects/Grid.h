#pragma once

#include "../Object.h"

class Grid : public Object
{
private:
	SDL_Point _startPoint;

	const int RowsAmount;
	const int ColumnsAmount;
	const int Width;
	const int Height;
	const int ColumnWidth = Width / ColumnsAmount;
	const int RowHeight = Height / RowsAmount;
public:
	Grid(const SDL_Point& position,
		 int rowsAmount,
		 int columnsAmount,
		 int width,
		 int height,
		 Color background) noexcept;

	void Show() const noexcept override;
};

