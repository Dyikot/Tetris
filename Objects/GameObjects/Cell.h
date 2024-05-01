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

	// ��������� ������
	void Show() override;

	// ��������� ������ � ������ �����������
	// \param coordinates - ���������� ��������� ����� ������
	void Show(const Coordinates& coordinates);

	// ����������� ������
	// \param movementSide - ������� � ������� ��������� ����������� ������.
	// �������: Left, Right, Down.
	void Move(MovementSide movementSide);
};

