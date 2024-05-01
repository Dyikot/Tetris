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

	//  оличество циклов дл€ начала движени€ тетрамино
	const int CyclesAmountToTetrominoMove = 80;

	// ’ранилище клеток упавших тетрамино
	std::vector<Cell> _cells = std::vector<Cell>(VerticalCellsNumber * HorizontalCellsNumber);

	// —етка пол€
	Grid _grid = Grid(
		/*startPoint*/ { .x = 0, .y = 0 },
		/*rowsAmount*/ VerticalCellsNumber,
		/*columnsAmount*/ HorizontalCellsNumber,
		/*width*/ FieldWidth* WidthScale,	
		/*height*/ FieldHeight* HeightScale,
		/*backgound*/ Colors::Grey
	);

	// „исло пройденных циклов
	int _cyclesCompleted = 0;

	// “етрамино
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

	// ”правл€емое игроком тетрамино 
	Tetromino _activeTetromino = SelectTetriminoRandomly();

	// ƒоступно перевыбор фигуры
	bool _isReselectAvaliable = true;

	// “ребутес€ ли фигуру сбрасывать
	bool _isDropRequired = false;
public:
	GameScene() = default;
		
	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;
private:
	// ¬ыбирает тетрамино случайный образом со случайным цветом
	Tetromino SelectTetriminoRandomly() const;

	// ѕроверка на то, требуетс€ ли перемещать фигуру
	bool IsTetrominoShouldMove();

	// ќпредел€ет состо€ние тетрамино, путем проверки дошла ли тетрамино
	// до упавших тетрамино и если дошла то требуетс€ ли очистить строки,
	// низа игрового пол€, вверхней границы игрового пол€
	TetrominoState GetTetrominoState();

	// ѕоиск заполненных строк
	// \return ¬озвращает  массив индексов заполненных строк
	std::vector<int> FindFullRows();

	// ќчищает заполненные строки
	// \param removeRowsIndexes - массив индексов заполненных строк
	void ClearRows(const std::vector<int>& removeRowsIndexes);

	// ќтображает упавшие тетрамино
	void ShowDroppedTetrominoes();

	// \param cell - клетка, дл€ которой требуетс€ найти индекс на поле _cells
	// \return ¬озвращает  индекс клетки на поле _cells
	int GetIndexFrom(const Cell& cell);

	// ѕолучить индекс нижний клетки относительно клетки в хранилище упавших тетрамино
	//\param cell - клетка игрового пол€
	//\returns »ндекс нижней клетки
	int GetLowerIndexFrom(const Cell& cell);

	// —охран€ет клетки упавшей тетерамино в массиве _cells
	// \param cells - клетки, которые требуетс€ сохранить
	void AddCellsToDroppedCellsStorage(const std::array<Cell, 4>& cells);
};