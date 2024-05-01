#pragma once

#include <vector>
#include <array>
#include <numbers>
#include <functional>

#include "Cell.h" 

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
	Tetromino(TetrominoType type, const std::array<Cell, 4>& cellStartPoints):
		_type(type),
		_cells(cellStartPoints){}

	void Show() override;

	void Move(MovementSide movementSide);

	void Rotate();

	// �������� �� ��, �� ����� �� ��������� �� ����� ������� �������� ����
	// \param left - ����� ������� �������� ����.	
	bool IsOutLeftBorder(int left) const;

	// �������� �� ��, �� ����� �� ��������� �� ����� ������� �������� ����
	// \param right - ������ ������� �������� ����.
	bool IsOutRightBorder(int right) const;

	// �������� �� ��, �� ����� �� ��������� �� ������� �������� ����.
	// � ���� ����� ��, ������������ ���������, ��������� � ������� �������� ����
	// \param left - ����� ������� �������� ����.
	// \param right - ������ ������� �������� ����.
	// \param top - ������� ������� �������� ����.
	void CorrectCoordinates(int left, int right, int top);

	const std::array<Cell, 4>& GetCells() const;

	// ������������ ����� ��������� ����� ������, ������� ����������� ���� ���������
	// \return ����������  ���������� �����
	const Coordinates& GetLowestCoordinates() const;

	// ������������ ����� ��������� ����� ������, ������� ����������� ���� ���������
	// \return ����������  ���������� �����
	const Coordinates& GetHighestCoordinates() const;

	void SetBackground(Colors background) override;

	// ���������� ����� ������ ������� ���������� ��������
	// \param tetrominoType - ��� ���������
	// \return ����������  ������ ����� ������� _cells 
	int SelectRotationCenter(TetrominoType tetrominoType) const;
};