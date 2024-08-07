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

