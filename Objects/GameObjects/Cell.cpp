#include "Cell.h"
#include "../Scenes/Scene.h"

Cell::Cell(Texture& cellTexture,
		   const SDL_Point position,
		   const SDL_Color& background) noexcept:
	_cellTexture(cellTexture),
	Position(position),
	Background(background)
{
	
}

void Cell::OnRender() const noexcept
{
	OnRender(Position);
}

void Cell::OnRender(const SDL_Point& position) const noexcept
{
	SDL_Rect rectangle =
	{
		.x = position.x * Scene::Scale,
		.y = position.y * Scene::Scale,
		.w = Size * Scene::Scale,
		.h = Size * Scene::Scale
	};

	_cellTexture.SetColor(Background);
	_cellTexture.Render(rectangle);
}


void Cell::Move(MovementSide movementSide) noexcept
{
	switch(movementSide)
	{
		case MovementSide::Left:
		{
			Position.x -= Size;
			break;
		}			

		case MovementSide::Right:
		{
			Position.x += Size;
			break;
		}			

		case MovementSide::Down:
		{
			Position.y += Size;
			break;
		}			

		case MovementSide::Up:
		{
			Position.y -= Size;
			break;
		}
	}
}

Cell& Cell::operator=(const Cell& other)
{
	Position = other.Position;
	_cellTexture = other._cellTexture;
	Background = other.Background;

	return *this;
}
