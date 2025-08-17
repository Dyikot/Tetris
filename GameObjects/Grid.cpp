#include "Grid.h"

Grid::Grid(SDL_Point position,
		   int rowsAmount, 
		   int columnsAmount,
		   int width, 
		   int height, 
		   SDL_Color lineColor) noexcept:
	Position(position),
	Rows(rowsAmount),
	Columns(columnsAmount),
	Width(width),
	Height(height),
	LineColor(lineColor)
{}

void Grid::Render(SDL_Renderer * renderer) const
{
	SetRenderColor(renderer, LineColor);

	for(int x = ColumnWidth; x < Width; x += ColumnWidth)
	{
		SDL_RenderDrawLine(renderer, x, Position.y, x, Height);
	}

	for(int y = RowHeight; y < Height; y += RowHeight)
	{
		SDL_RenderDrawLine(renderer, Position.x, y, Width, y);
	}
}