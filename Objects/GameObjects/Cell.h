#pragma once

#include"../Object.h"
#include "../../BasicStructs/MovementSide.h"
#include "../../Style/Texture.h"

class Cell: public Object
{
public:
	static constexpr int Size = 10;
	SDL_Point StartPoint;
private:
	Texture* _cellTexture;
public:
	Cell(Texture* cellTexture = nullptr,
		 const SDL_Point startPoint = { .x = 0 , .y = 0 },
		 Color background = Cell::DefaultBackgroundColor) noexcept;

	/// <summary>
	/// ќтрисовка клетки
	/// </summary>
	void Show() noexcept override;
	
	/// <summary>
	/// ќтрисовка клетки в других координатах
	/// </summary>
	/// <param name="coordinates">- координаты начальной точки клетки</param>
	void Show(const SDL_Point& coordinates) noexcept;

	/// <summary>
	/// ѕеремещение клетки
	/// </summary>
	/// <param name="movementSide">- сторона перемещени€: Left, Right, Down.</param>
	void Move(MovementSide movementSide) noexcept;
};

