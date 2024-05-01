#pragma once

#include"..\Object.h"
#include "..\..\BasicStructs\MovementSide.h"

class Cell: public Object
{
public:
	static const int Size = 10;
	Coordinates StartPoint;
public:
	Cell(const Coordinates startPoint = {.x = 0, .y = 0}, Colors color = Colors::None):
		StartPoint(startPoint),
		Object(color){}

	// ќтрисовка клетки
	void Show() override;

	// ќтрисовка клетки в других координатах
	// \param coordinates - координаты начальной точки клетки
	void Show(const Coordinates& coordinates);

	// ѕеремещение клетки
	// \param movementSide - сторона в которую требуетс€ переместить клетку.
	// —тороны: Left, Right, Down.
	void Move(MovementSide movementSide);
};

