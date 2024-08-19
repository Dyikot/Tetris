#pragma once

#include <vector>
#include <array>
#include <numbers>
#include <functional>
#include <algorithm>

#include "../Cell.h"
#include "../../Style/Texture.h"

enum class TetrominoType
{
	I, J, L, O, S, T, Z
};

class Tetromino : public Object
{
protected:
	TetrominoType _type;

	std::array<Cell, 4> _cells;
public:
	Tetromino(TetrominoType type, const std::array<Cell, 4>& cells) noexcept;

	void Show() const noexcept override;

	void Move(MovementSide movementSide) noexcept;

	void Rotate();

	void SetBackground(Color background) noexcept override;

	void CopyCoordinates(const Tetromino& tetromino) noexcept;

	/// <summary>
	/// �������� �� ��, �� ����� �� ��������� �� ������� �������� ����.
	/// � ���� ����� ��, ������������ ���������, ��������� � ������� �������� ����
	/// </summary>
	/// <param name="left">- ����� ������� �������� ����</param>
	/// <param name="right">- ������ ������� �������� ����</param>
	/// <param name="top">- ������� ������� �������� ����</param>
	void CorrectCoordinates(int left, int right, int top);

	bool IsOnRightBorder(int right) const noexcept;

	bool IsOnLeftBorder(int left) const noexcept;

	bool IsOutLeftBorder(int left) const noexcept;

	bool IsOutRightBorder(int right) const noexcept;

	bool IsOutTopBorder(int top) const noexcept;

	/// <summary>
	/// ���������� ����� ������ ������� ���������� ��������
	/// </summary>
	/// <param name="tetrominoType">- ��� ���������</param>
	/// <returns>���������� ����� ��������</returns>
	const SDL_Point& GetRotationCenter(TetrominoType tetrominoType) const;

	/// <summary>
	/// ����� ����� ������ ������
	/// </summary>
	/// <returns>���������� ��������� ������</returns>
	const Cell& GetLowestCell() const noexcept;

	/// <summary>
	/// ����� ����� ������� ������
	/// </summary>
	/// <returns>���������� ��������� ������</returns>
	const Cell& GetHighestCell() const noexcept;

	const std::array<Cell, 4>& GetCells() const noexcept;

	TetrominoType GetType() const noexcept;	
};