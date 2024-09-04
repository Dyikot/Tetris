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

	void OnRender() const noexcept override;

	void Move(MovementSide movementSide) noexcept;

	void Rotate();

	void SetBackground(const SDL_Color& background) noexcept;

	void CopyCoordinates(const Tetromino& tetromino) noexcept;

	/// <summary>
	/// Correct tetromino coordinates if its out grid's border
	/// </summary>
	/// <param name="left"> - left grid border</param>
	/// <param name="right"> - right grid border</param>
	/// <param name="top"> - top grid border</param>
	void CorrectCoordinates(int left, int right, int top);

	bool IsOnRightBorder(int right) const noexcept;

	bool IsOnLeftBorder(int left) const noexcept;

	bool IsOutLeftBorder(int left) const noexcept;

	bool IsOutRightBorder(int right) const noexcept;

	bool IsOutTopBorder(int top) const noexcept;

	const SDL_Point& GetRotationCenter(Type tetrominoType) const;

	const Cell& GetLowestCell() const noexcept;

	const Cell& GetHighestCell() const noexcept;

	const std::array<Cell, 4>& GetCells() const noexcept;

	Type GetType() const noexcept;
private:
	std::array<Cell, 4> CreateCellsBy(Type type, Texture& cellTexture) const;
};