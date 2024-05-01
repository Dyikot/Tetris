#pragma once

#include "Scene.h"
#include "GameOverMenu.h"
#include "PauseMenu.h"
#include "..\Application\Application.h"
#include "..\Objects\GameObjects\Cell.h"
#include "..\Objects\GameObjects\Grid.h"
#include "..\Objects\GameObjects\Tetromino.h"
#include "Random/Random.h"

class GameScene: public Scene
{
private:
	const int HorizontalCellsNumber = 10;
	const int VerticalCellsNumber = 20;
	const int FieldWidth = HorizontalCellsNumber * Cell::Size;
	const int FieldHeight = VerticalCellsNumber * Cell::Size;
	const int WidthScale = Application::Current()->WindowWidth / FieldWidth;
	const int HeightScale = Application::Current()->WindowHeight / FieldHeight;

	// ���������� ������ ��� ������ �������� ���������
	const int CyclesAmountToTetrominoMove = 80;

	// ��������� ������ ������� ���������
	std::vector<Cell> _cells = std::vector<Cell>(VerticalCellsNumber * HorizontalCellsNumber);

	// ����� ����
	Grid _grid = Grid(
		/*startPoint*/ { .x = 0, .y = 0 },
		/*rowsAmount*/ VerticalCellsNumber,
		/*columnsAmount*/ HorizontalCellsNumber,
		/*width*/ FieldWidth* WidthScale,	
		/*height*/ FieldHeight* HeightScale,
		/*backgound*/ Colors::Grey
	);

	// ����� ���������� ������
	int _cyclesCompleted = 0;

	// ���������
	std::array<Tetromino, 7> _tetrominos = 
	{
		Tetromino(
			TetrominoType::I,
			std::array<Cell, 4>
			{
				Cell(Coordinates{.x = 30, .y = 0}),
				Cell(Coordinates{.x = 40, .y = 0}),
				Cell(Coordinates{.x = 50, .y = 0}),
				Cell(Coordinates{.x = 60, .y = 0})
			}			
		),
		Tetromino(
			TetrominoType::J,
			std::array<Cell, 4>
			{
				Cell(Coordinates{.x = 40, .y = 0}),
				Cell(Coordinates{.x = 40, .y = 10}),
				Cell(Coordinates{.x = 50, .y = 10}),
				Cell(Coordinates{.x = 60, .y = 10})
			}
		),
		Tetromino(
			TetrominoType::L,
			std::array<Cell, 4>
			{
				Cell(Coordinates{.x = 60, .y = 0}),
				Cell(Coordinates{.x = 60, .y = 10}),
				Cell(Coordinates{.x = 50, .y = 10}),
				Cell(Coordinates{.x = 40, .y = 10})
			}
		),
		Tetromino(
			TetrominoType::O,
			std::array<Cell, 4>
			{
				Cell(Coordinates{.x = 40, .y = 0}),
				Cell(Coordinates{.x = 50, .y = 0}),
				Cell(Coordinates{.x = 40, .y = 10}),
				Cell(Coordinates{.x = 50, .y = 10})
			}
		),
		Tetromino(
			TetrominoType::S,
			std::array<Cell, 4>
			{
				Cell(Coordinates{.x = 50, .y = 0}),
				Cell(Coordinates{.x = 60, .y = 0}),
				Cell(Coordinates{.x = 40, .y = 10}),
				Cell(Coordinates{.x = 50, .y = 10})
			}
		),
		Tetromino(
			TetrominoType::T,
			std::array<Cell, 4>
			{
				Cell(Coordinates{.x = 50, .y = 0}),
				Cell(Coordinates{.x = 40, .y = 10}),
				Cell(Coordinates{.x = 50, .y = 10}),
				Cell(Coordinates{.x = 60, .y = 10})
			}
		),
		Tetromino(
			TetrominoType::Z,
			std::array<Cell, 4>
			{
				Cell(Coordinates{.x = 40, .y = 0}),
				Cell(Coordinates{.x = 50, .y = 0}),
				Cell(Coordinates{.x = 50, .y = 10}),
				Cell(Coordinates{.x = 60, .y = 10})
			}
		)
	};

	// ����������� ������� ��������� 
	Tetromino _activeTetromino = SelectTetriminoRandomly();

	// �������� ��������� ������
	bool _isReselectAvaliable = true;

	// ��������� �� ������ ����������
	bool _isDropRequired = false;
public:
	GameScene() = default;
		
	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;
private:
	// �������� ��������� ��������� ������� �� ��������� ������
	Tetromino SelectTetriminoRandomly() const;

	// �������� �� ��, ��������� �� ���������� ������
	bool IsTetrominoShouldMove();

	// ���������� ��������� ���������, ����� �������� ����� �� ���������
	// �� ������� ��������� � ���� ����� �� ��������� �� �������� ������,
	// ���� �������� ����, �������� ������� �������� ����
	TetrominoState GetTetrominoState();

	// ����� ����������� �����
	// \return ����������  ������ �������� ����������� �����
	std::vector<int> FindFullRows();

	// ������� ����������� ������
	// \param removeRowsIndexes - ������ �������� ����������� �����
	void ClearRows(const std::vector<int>& removeRowsIndexes);

	// ���������� ������� ���������
	void ShowDroppedTetrominoes();

	// \param cell - ������, ��� ������� ��������� ����� ������ �� ���� _cells
	// \return ����������  ������ ������ �� ���� _cells
	int GetIndexFrom(const Cell& cell);

	// �������� ������ ������ ������ ������������ ������ � ��������� ������� ���������
	//\param cell - ������ �������� ����
	//\returns ������ ������ ������
	int GetLowerIndexFrom(const Cell& cell);

	// ��������� ������ ������� ���������� � ������� _cells
	// \param cells - ������, ������� ��������� ���������
	void AddCellsToDroppedCellsStorage(const std::array<Cell, 4>& cells);
};