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
	/// Проверка на то, не зашло ли тетрамино за левую границу игрового поля
	/// </summary>
	/// <param name="left">- левая граница игрового поля</param>
	bool IsOutLeftBorder(int left) const noexcept;

	/// <summary>
	/// Проверка на то, не зашло ли тетрамино за правую границу игрового поля
	/// </summary>
	/// <param name="right">- правая граница игрового поля</param>
	/// <returns></returns>
	bool IsOutRightBorder(int right) const noexcept;

	/// <summary>
	/// Проверка на то, не зашло ли тетрамино за границу игрового поля.
	/// И если зашло то, корректирует положение, перемещая в границы игрового поля
	/// </summary>
	/// <param name="left">- левая граница игрового поля</param>
	/// <param name="right">- правая граница игрового поля</param>
	/// <param name="top">- верхняя граница игрового поля</param>
	void CorrectCoordinates(int left, int right, int top);

	const std::array<Cell, 4>& GetCells() const noexcept;

	/// <summary>
	/// Поиск самой низкой клетки
	/// </summary>
	/// <returns>Возвращает найденную клетку</returns>
	const Cell& GetLowestCell() const noexcept;

	/// <summary>
	/// Поиск самой высокой клетки
	/// </summary>
	/// <returns>Возвращает найденную клетку</returns>
	const Cell& GetHighestCell() const noexcept;

	void SetBackground(Color background) noexcept override;

	void CopyCoordinates(const Tetromino& tetromino) noexcept;

	/// <summary>
	/// Выбирается точка вокруг которой происходит вращение
	/// </summary>
	/// <param name="tetrominoType">- тип тетрамино</param>
	/// <returns>Возвращает индекс точки массива _cells </returns>
	int SelectRotationCenter(TetrominoType tetrominoType) const;
};