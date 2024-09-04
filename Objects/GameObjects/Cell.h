#pragma once

#include"../Object.h"
#include "../../BasicStructs/MovementSide.h"
#include "../../Graphics/Texture.h"
#include "../../Graphics/Colors.h"

class Cell: public Object
{
public:
	static constexpr int Size = 10;
	SDL_Point Position;
	SDL_Color Background;
private:
	Texture& _cellTexture;
public:
	Cell(Texture& cellTexture,
		 const SDL_Point position = { .x = 0 , .y = 0 },
		 const SDL_Color& background = Colors::Transparent) noexcept;

	/// <summary>
	/// ќтрисовка клетки
	/// </summary>
	void OnRender() const noexcept override;
	
	/// <summary>
	/// ќтрисовка клетки в других координатах
	/// </summary>
	/// <param name="coordinates">- координаты начальной точки клетки</param>
	void OnRender(const SDL_Point& coordinates) const noexcept;

	/// <summary>
	/// ѕеремещение клетки
	/// </summary>
	/// <param name="movementSide">- сторона перемещени€: Left, Right, Down.</param>
	void Move(MovementSide movementSide) noexcept;

	Cell& operator=(const Cell& other);
};