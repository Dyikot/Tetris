#pragma once

#include "../Object.h"

class Grid : public Object
{
public:
	const SDL_Point Position;
	const int Rows;
	const int Columns;
	const int Width;
	const int Height;
	const int ColumnWidth = Width / Columns;
	const int RowHeight = Height / Rows;
	SDL_Color LineColor;
public:
	Grid(const SDL_Point& position,
		 int rows,
		 int columns,
		 int width,
		 int height,
		 const SDL_Color& lineColor) noexcept;

	void Show() const noexcept override;
};

