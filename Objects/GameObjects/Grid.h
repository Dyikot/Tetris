#pragma once

#include "..\Object.h"

class Grid : public Object
{
private:
	Coordinates _startPoint;
	const int RowsAmount;
	const int ColumnsAmount;
	const int Width;
	const int Height;
	const int ColumnWidth = Width / ColumnsAmount;
	const int RowHeight = Height / RowsAmount;
public:
	Grid(
		const Coordinates& startPoint,
		int rowsAmount, 
		int columnsAmount,
		int width,
		int height,
		Colors background
	):
		_startPoint(startPoint),
		RowsAmount(rowsAmount),
		ColumnsAmount(columnsAmount),
		Width(width),
		Height(height),
		Object(background){}

	void Show() override;
};

