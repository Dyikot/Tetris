#pragma once

#include"../Object.h"
#include "../../BasicStructs/MovementSide.h"
#include "../../Graphics/Texture.h"

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
	/// ��������� ������
	/// </summary>
	void Show() const noexcept override;
	
	/// <summary>
	/// ��������� ������ � ������ �����������
	/// </summary>
	/// <param name="coordinates">- ���������� ��������� ����� ������</param>
	void Show(const SDL_Point& coordinates) const noexcept;

	/// <summary>
	/// ����������� ������
	/// </summary>
	/// <param name="movementSide">- ������� �����������: Left, Right, Down.</param>
	void Move(MovementSide movementSide) noexcept;

	Cell& operator=(const Cell& other);
};

