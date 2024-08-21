#include "Grid.h"

Grid::Grid(const SDL_Point& position,
		   int rowsAmount, 
		   int columnsAmount,
		   int width, 
		   int height, 
		   const SDL_Color& background) noexcept:
	Object(background),
	Position(position),
	Rows(rowsAmount),
	Columns(columnsAmount),
	Width(width),
	Height(height)	
{

}

void Grid::Show() const noexcept
{
	SetRenderColor(_renderer, _backgroud);

	for(int x = ColumnWidth; x < Width; x += ColumnWidth)
	{
		SDL_RenderDrawLine(_renderer, x, Position.y, x, Height);
	}

	for(int y = RowHeight; y < Height; y += RowHeight)
	{
		SDL_RenderDrawLine(_renderer, Position.x, y, Width, y);
	}
}