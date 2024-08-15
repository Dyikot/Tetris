#pragma once

#include <vector>
#include <array>
#include <numbers>
#include <functional>
#include <algorithm>

#include "Cell.h"
#include "../../Style/Texture.h"

enum class TetrominoType
{
	I, J, L, O, S, T, Z
};

enum class TetrominoState
{
	Moving,
	Dropped,
	BeyoundUppedBorder
};

class Tetromino : public Object
{
private:
	TetrominoType _type;
	std::array<Cell, 4> _cells;
public:
	Tetromino(TetrominoType type, const std::array<Cell, 4>& cellStartPoints) noexcept;

	void Show() const noexcept override;

	void Move(MovementSide movementSide) noexcept;

	void Rotate();

	/// <summary>
	/// �������� �� ��, �� ����� �� ��������� �� ����� ������� �������� ����
	/// </summary>
	/// <param name="left">- ����� ������� �������� ����</param>
	bool IsOutLeftBorder(int left) const noexcept;

	/// <summary>
	/// �������� �� ��, �� ����� �� ��������� �� ������ ������� �������� ����
	/// </summary>
	/// <param name="right">- ������ ������� �������� ����</param>
	/// <returns></returns>
	bool IsOutRightBorder(int right) const noexcept;

	/// <summary>
	/// �������� �� ��, �� ����� �� ��������� �� ������� �������� ����.
	/// � ���� ����� ��, ������������ ���������, ��������� � ������� �������� ����
	/// </summary>
	/// <param name="left">- ����� ������� �������� ����</param>
	/// <param name="right">- ������ ������� �������� ����</param>
	/// <param name="top">- ������� ������� �������� ����</param>
	void CorrectCoordinates(int left, int right, int top);

	const std::array<Cell, 4>& GetCells() const noexcept;

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

	void SetBackground(Color background) noexcept override;

	void CopyCoordinates(const Tetromino& tetromino) noexcept;

	/// <summary>
	/// ���������� ����� ������ ������� ���������� ��������
	/// </summary>
	/// <param name="tetrominoType">- ��� ���������</param>
	/// <returns>���������� ������ ����� ������� _cells </returns>
	int SelectRotationCenter(TetrominoType tetrominoType) const;
};