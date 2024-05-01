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

	// ѕроверка на то, не зашло ли тетрамино за левую границу игрового пол€
	// \param left - Ћева€ граница игрового пол€.	
	bool IsOutLeftBorder(int left) const;

	// ѕроверка на то, не зашло ли тетрамино за левую границу игрового пол€
	// \param right - ѕрава€ граница игрового пол€.
	bool IsOutRightBorder(int right) const;

	// ѕроверка на то, не зашло ли тетрамино за границу игрового пол€.
	// » если зашло то, корректирует положение, перемеща€ в границы игрового пол€
	// \param left - Ћева€ граница игрового пол€.
	// \param right - ѕрава€ граница игрового пол€.
	// \param top - ¬ерхн€€ граница игрового пол€.
	void CorrectCoordinates(int left, int right, int top);

	const std::array<Cell, 4>& GetCells() const;

	// ѕроизводитс€ поиск стартовой точки клетки, котора€ расположена выше остальных
	// \return ¬озвращает  координаты точки
	const Coordinates& GetLowestCoordinates() const;

	// ѕроизводитс€ поиск стартовой точки клетки, котора€ расположена ниже остальных
	// \return ¬озвращает  координаты точки
	const Coordinates& GetHighestCoordinates() const;

	void SetBackground(Colors background) override;

	// ¬ыбираетс€ точка вокруг которой происходит вращение
	// \param tetrominoType - тип тетрамино
	// \return ¬озвращает  индекс точки массива _cells 
	int SelectRotationCenter(TetrominoType tetrominoType) const;
};