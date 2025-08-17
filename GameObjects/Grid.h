#pragma once

#include "../Render/Renderable.h"
#include "../Base/Colors.h"

class Grid : public Renderable
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
	Grid(SDL_Point position,
		 int rows,
		 int columns,
		 int width,
		 int height,
		 SDL_Color lineColor) noexcept;

	void Render(SDL_Renderer* renderer) const override;
};