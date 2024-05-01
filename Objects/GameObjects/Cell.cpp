#include "Cell.h"

void Cell::Show()
{
	SDL_Rect body =
	{
		.x = StartPoint.x * 4,
		.y = StartPoint.y * 4,
		.w = Size * 4,
		.h = Size * 4
	};

	Color::SetRenderColor(_renderer, _backgroud);
	SDL_RenderFillRect(_renderer, &body);
}

void Cell::Show(const Coordinates& startPoint)
{
	SDL_Rect body =
	{
		.x = startPoint.x * 4,
		.y = startPoint.y * 4,
		.w = Size * 4,
		.h = Size * 4
	};

	Color::SetRenderColor(_renderer, _backgroud);
	SDL_RenderFillRect(_renderer, &body);
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
