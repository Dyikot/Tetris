#pragma once

#include <vector>
#include <array>
#include <numbers>
#include <functional>
#include <algorithm>

#include "Cell.h"
#include "../../Graphics/Texture.h"

class Tetromino : public Object
{
public:
	enum class Type
	{
		I, J, L, O, S, T, Z
	};
protected:
	Type _type;
	std::array<Cell, 4> _cells;
public:
	Tetromino(Type type, Texture& cellTexture) noexcept;

	void Show() const noexcept override;

	void Move(MovementSide movementSide) noexcept;

	void Rotate();

	void SetBackground(const SDL_Color& background) noexcept;

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
	const SDL_Point& GetRotationCenter(Type tetrominoType) const;

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

	Type GetType() const noexcept;	

private:
	std::array<Cell, 4> CreateCellsBy(Type type, Texture& cellTexture) const;
};