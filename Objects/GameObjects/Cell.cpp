#include "Cell.h"

Cell::Cell(Texture* cellTexture, const SDL_Point position, Color background) noexcept:
	_cellTexture(cellTexture),
	Position(position),
	Object(background)
{

}

void Cell::Show() const noexcept
{
	Show(Position);
}

void Cell::Show(const SDL_Point& position) const noexcept
{
	SDL_Rect rectangle =
	{
		.x = position.x * Scene::Scale,
		.y = position.y * Scene::Scale,
		.w = Size * Scene::Scale,
		.h = Size * Scene::Scale
	};
	
	Colors::SetTextureColor(*_cellTexture, _backgroud);
	_cellTexture->Render(_renderer, rectangle);
}


void Cell::Move(MovementSide movementSide) noexcept
{
	switch(movementSide)
	{
		case MovementSide::Left:
			Position.x -= Size;
			break;

		case MovementSide::Right:
			Position.x += Size;
			break;

		case MovementSide::Down:
			Position.y += Size;
			break;

		case MovementSide::Up:
			Position.y -= Size;
			break;

		default:
			break;
	}
}
