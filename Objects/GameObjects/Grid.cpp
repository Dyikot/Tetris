#include "Grid.h"

Grid::Grid(const SDL_Point& position,
		   int rowsAmount, 
		   int columnsAmount,
		   int width, 
		   int height, 
		   const SDL_Color& lineColor) noexcept:
	Position(position),
	Rows(rowsAmount),
	Columns(columnsAmount),
	Width(width),
	Height(height),
	LineColor(lineColor)
{

}

void Grid::Show() const noexcept
{
	SetRenderColor(_renderer, LineColor);

	for(int x = ColumnWidth; x < Width; x += ColumnWidth)
	{
		SDL_RenderDrawLine(_renderer, x, Position.y, x, Height);
	}

	for(int y = RowHeight; y < Height; y += RowHeight)
	{
		SDL_RenderDrawLine(_renderer, Position.x, y, Width, y);
	}
}