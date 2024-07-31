#pragma once

#include"..\Object.h"
#include "..\..\BasicStructs\MovementSide.h"

class Cell: public Object
{
public:
	static const int Size = 10;
	Coordinates StartPoint;
public:
	Cell(const Coordinates startPoint = {.x = 0, .y = 0},
		 Color background = Cell::DefaultBackgroundColor):
		StartPoint(startPoint),
		Object(background){}

	/// <summary>
	/// ��������� ������
	/// </summary>
	void Show() override;

	/// <summary>
	/// ��������� ������ � ������ �����������
	/// </summary>
	/// <param name="coordinates">- ���������� ��������� ����� ������</param>
	void Show(const Coordinates& coordinates);

	/// <summary>
	/// ����������� ������
	/// </summary>
	/// <param name="movementSide">- ������� �����������: Left, Right, Down.</param>
	void Move(MovementSide movementSide);
};

