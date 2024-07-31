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

	/// <summary>
	/// Проверка на то, не зашло ли тетрамино за левую границу игрового поля
	/// </summary>
	/// <param name="left">- левая граница игрового поля</param>
	bool IsOutLeftBorder(int left) const;

	/// <summary>
	/// Проверка на то, не зашло ли тетрамино за правую границу игрового поля
	/// </summary>
	/// <param name="right">- правая граница игрового поля</param>
	/// <returns></returns>
	bool IsOutRightBorder(int right) const;

	/// <summary>
	/// Проверка на то, не зашло ли тетрамино за границу игрового поля.
	/// И если зашло то, корректирует положение, перемещая в границы игрового поля
	/// </summary>
	/// <param name="left">- левая граница игрового поля</param>
	/// <param name="right">- правая граница игрового поля</param>
	/// <param name="top">- верхняя граница игрового поля</param>
	void CorrectCoordinates(int left, int right, int top);

	const std::array<Cell, 4>& GetCells() const;

	/// <summary>
	/// Производится поиск стартовой точки клетки, которая расположена выше остальных
	/// </summary>
	/// <returns>Возвращает  координаты точки</returns>
	const Coordinates& GetLowestCoordinates() const;

	/// <summary>
	/// Производится поиск стартовой точки клетки, которая расположена ниже остальных
	/// </summary>
	/// <returns>Возвращает  координаты точки</returns>
	const Coordinates& GetHighestCoordinates() const;

	void SetBackground(Color background) override;

	/// <summary>
	/// Выбирается точка вокруг которой происходит вращение
	/// </summary>
	/// <param name="tetrominoType">- тип тетрамино</param>
	/// <returns>Возвращает индекс точки массива _cells </returns>
	int SelectRotationCenter(TetrominoType tetrominoType) const;
};