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
	Tetromino(TetrominoType type, const std::array<Cell, 4>& cellStartPoints);

	void Show() override;

	void Move(MovementSide movementSide);

	void Rotate();

	/// <summary>
	/// �������� �� ��, �� ����� �� ��������� �� ����� ������� �������� ����
	/// </summary>
	/// <param name="left">- ����� ������� �������� ����</param>
	bool IsOutLeftBorder(int left) const;

	/// <summary>
	/// �������� �� ��, �� ����� �� ��������� �� ������ ������� �������� ����
	/// </summary>
	/// <param name="right">- ������ ������� �������� ����</param>
	/// <returns></returns>
	bool IsOutRightBorder(int right) const;

	/// <summary>
	/// �������� �� ��, �� ����� �� ��������� �� ������� �������� ����.
	/// � ���� ����� ��, ������������ ���������, ��������� � ������� �������� ����
	/// </summary>
	/// <param name="left">- ����� ������� �������� ����</param>
	/// <param name="right">- ������ ������� �������� ����</param>
	/// <param name="top">- ������� ������� �������� ����</param>
	void CorrectCoordinates(int left, int right, int top);

	const std::array<Cell, 4>& GetCells() const;

	/// <summary>
	/// ����� ����� ������ ������
	/// </summary>
	/// <returns>���������� ��������� ������</returns>
	const Cell& GetLowestCell() const;

	/// <summary>
	/// ����� ����� ������� ������
	/// </summary>
	/// <returns>���������� ��������� ������</returns>
	const Cell& GetHighestCell() const;

	void SetBackground(Color background) override;

	void CopyCoordinates(const Tetromino& tetromino);

	/// <summary>
	/// ���������� ����� ������ ������� ���������� ��������
	/// </summary>
	/// <param name="tetrominoType">- ��� ���������</param>
	/// <returns>���������� ������ ����� ������� _cells </returns>
	int SelectRotationCenter(TetrominoType tetrominoType) const;
};