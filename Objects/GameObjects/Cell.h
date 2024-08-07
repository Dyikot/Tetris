#pragma once

#include"../Object.h"
#include "../../BasicStructs/MovementSide.h"
#include "../../Style/Texture.h"

class Cell: public Object
{
public:
	static constexpr int Size = 10;
	Coordinates StartPoint;
private:
	Texture* _cellTexture;
public:
	Cell(Texture* cellTexture = nullptr,
		 const Coordinates startPoint = { .x = 0 , .y = 0 },
		 Color background = Cell::DefaultBackgroundColor);

	/// <summary>
	/// ќтрисовка клетки
	/// </summary>
	void Show() override;
	
	/// <summary>
	/// ќтрисовка клетки в других координатах
	/// </summary>
	/// <param name="coordinates">- координаты начальной точки клетки</param>
	void Show(const Coordinates& coordinates);

	/// <summary>
	/// ѕеремещение клетки
	/// </summary>
	/// <param name="movementSide">- сторона перемещени€: Left, Right, Down.</param>
	void Move(MovementSide movementSide);
};

