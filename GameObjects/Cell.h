#pragma once

#include"../Render/Renderable.h"
#include "../Base/MovementSide.h"
#include "../Base/Texture.h"
#include "../Base/Colors.h"

class Cell: public Renderable
{
public:
	static constexpr int Size = 10;
	SDL_Point Position;
	SDL_Color Background;
private:
	Texture& _cellTexture;
public:
	Cell(Texture& cellTexture,
		 SDL_Point position = {},
		 SDL_Color background = Colors::Transparent) noexcept;

	void Render(SDL_Renderer* renderer) const override;
	void Render(SDL_Renderer* renderer, SDL_Point coordinates) const;
	void Move(MovementSide movementSide) noexcept;

	Cell& operator=(const Cell& other);
};