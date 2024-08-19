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
	/// ѕроверка на то, не зашло ли тетрамино за границу игрового пол€.
	/// » если зашло то, корректирует положение, перемеща€ в границы игрового пол€
	/// </summary>
	/// <param name="left">- лева€ граница игрового пол€</param>
	/// <param name="right">- права€ граница игрового пол€</param>
	/// <param name="top">- верхн€€ граница игрового пол€</param>
	void CorrectCoordinates(int left, int right, int top);

	bool IsOnRightBorder(int right) const noexcept;

	bool IsOnLeftBorder(int left) const noexcept;

	bool IsOutLeftBorder(int left) const noexcept;

	bool IsOutRightBorder(int right) const noexcept;

	bool IsOutTopBorder(int top) const noexcept;

	/// <summary>
	/// ¬ыбираетс€ точка вокруг которой происходит вращение
	/// </summary>
	/// <param name="tetrominoType">- тип тетрамино</param>
	/// <returns>¬озвращает точку вращени€</returns>
	const SDL_Point& GetRotationCenter(TetrominoType tetrominoType) const;

	/// <summary>
	/// ѕоиск самой низкой клетки
	/// </summary>
	/// <returns>¬озвращает найденную клетку</returns>
	const Cell& GetLowestCell() const noexcept;

	/// <summary>
	/// ѕоиск самой высокой клетки
	/// </summary>
	/// <returns>¬озвращает найденную клетку</returns>
	const Cell& GetHighestCell() const noexcept;

	const std::array<Cell, 4>& GetCells() const noexcept;

	TetrominoType GetType() const noexcept;	
};