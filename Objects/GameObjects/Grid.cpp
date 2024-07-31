#include "Grid.h"

void Grid::Show()
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