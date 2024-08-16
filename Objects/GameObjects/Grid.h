#pragma once

#include "../Object.h"

class Grid : public Object
{
private:
	SDL_Point _startPoint;

	const int Rows;
	const int Columns;
	const int Width;
	const int Height;
	const int ColumnWidth = Width / Columns;
	const int RowHeight = Height / Rows;
public:
	Grid(const SDL_Point& position,
		 int rows,
		 int columns,
		 int width,
		 int height,
		 Color background) noexcept;

	void Show() const noexcept override;
};

