#include "Cell.h"

Cell::Cell(Texture* cellTexture, const Coordinates startPoint, Color background):
	_cellTexture(cellTexture),
	StartPoint(startPoint),
	Object(background)
{

}

void Cell::Show()
{
	Show(StartPoint);
}

void Cell::Show(const Coordinates& startPoint)
{
	SDL_Rect rectangle =
	{
		.x = startPoint.x * 4,
		.y = startPoint.y * 4,
		.w = Size * 4,
		.h = Size * 4
	};
	
	Colors::SetTextureColor(*_cellTexture, _backgroud);
	_cellTexture->Render(_renderer, rectangle);
}


void Cell::Move(MovementSide movementSide)
{
	switch(movementSide)
	{
		case MovementSide::Left:
			StartPoint.x -= Size;
			break;

		case MovementSide::Right:
			StartPoint.x += Size;
			break;

		case MovementSide::Down:
			StartPoint.y += Size;
			break;

		default:
			break;
	}
}
