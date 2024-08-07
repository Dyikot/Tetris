#include "Grid.h"

Grid::Grid(const SDL_Point& startPoint,
		   int rowsAmount, 
		   int columnsAmount,
		   int width, 
		   int height, 
		   Color background) noexcept:
	_startPoint(startPoint),
	RowsAmount(rowsAmount),
	ColumnsAmount(columnsAmount),
	Width(width),
	Height(height),
	Object(background)
{

}

void Grid::Show() noexcept
{
	Colors::SetRenderColor(_renderer, _backgroud);

	for(int x = ColumnWidth; x < Width; x += ColumnWidth)
	{
		SDL_RenderDrawLine(_renderer, x, _startPoint.y, x, Height);
	}

	for(int y = RowHeight; y < Height; y += RowHeight)
	{
		SDL_RenderDrawLine(_renderer, _startPoint.x, y, Width, y);
	}
}