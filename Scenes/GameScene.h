#pragma once

#include <iostream>

#include "Scene.h"
#include "GameOverMenu.h"
#include "PauseMenu.h"
#include "..\Application\Application.h"
#include "..\Objects\GameObjects\Cell.h"
#include "..\Objects\GameObjects\Grid.h"
#include "..\Objects\GameObjects\Tetromino.h"
#include "..\Events\HoldKeyEvent.h"
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
	const int TicksAmountToTetrominoMove = 80;
	
	Random _random;

	//  летки упавших тетрамино
	std::vector<Cell> _cells = std::vector<Cell>(VerticalCellsNumber * HorizontalCellsNumber);

	// —етка пол€
	Grid _grid = Grid(/*startPoint*/ { .x = 0, .y = 0 },
					  /*rowsAmount*/ VerticalCellsNumber,
					  /*columnsAmount*/ HorizontalCellsNumber,
					  /*width*/ FieldWidth * WidthScale,	
					  /*height*/ FieldHeight * HeightScale,
					  /*backgound*/ Color::Grey);

	// „исло пройденных циклов
	int _ticksNumber = 0;
	
	// “етрамино
	std::array<Tetromino, 7> _tetrominos = 
	{
		Tetromino(TetrominoType::I,
				  std::array<Cell, 4>
				  {
					  Cell(Coordinates{ .x = 30, .y = 0 }),
					  Cell(Coordinates{ .x = 40, .y = 0 }),
					  Cell(Coordinates{ .x = 50, .y = 0 }),
					  Cell(Coordinates{ .x = 60, .y = 0 })
				  }),
		Tetromino(TetrominoType::J,
				  std::array<Cell, 4>
				  {
				  	  Cell(Coordinates{ .x = 40, .y = 0 }),
				  	  Cell(Coordinates{ .x = 40, .y = 10 }),
				  	  Cell(Coordinates{ .x = 50, .y = 10 }),
				  	  Cell(Coordinates{ .x = 60, .y = 10 })
				  }),
		Tetromino(TetrominoType::L,
				  std::array<Cell, 4>
				  {
				  	  Cell(Coordinates{ .x = 60, .y = 0 }),
				  	  Cell(Coordinates{ .x = 60, .y = 10 }),
				  	  Cell(Coordinates{ .x = 50, .y = 10 }),
				  	  Cell(Coordinates{ .x = 40, .y = 10 })
				  }),
		Tetromino(TetrominoType::O,
				  std::array<Cell, 4>
				  {
				  	  Cell(Coordinates{ .x = 40, .y = 0 }),
				  	  Cell(Coordinates{ .x = 50, .y = 0 }),
				  	  Cell(Coordinates{ .x = 40, .y = 10 }),
				  	  Cell(Coordinates{ .x = 50, .y = 10 })
				  }),
		Tetromino(TetrominoType::S,
				  std::array<Cell, 4>
				  {
				  	  Cell(Coordinates{ .x = 50, .y = 0 }),
				  	  Cell(Coordinates{ .x = 60, .y = 0 }),
				  	  Cell(Coordinates{ .x = 40, .y = 10 }),
				  	  Cell(Coordinates{ .x = 50, .y = 10 })
				  }),
		Tetromino(TetrominoType::T,
				  std::array<Cell, 4>
				  {
				  	  Cell(Coordinates{ .x = 50, .y = 0 }),
				  	  Cell(Coordinates{ .x = 40, .y = 10 }),
				  	  Cell(Coordinates{ .x = 50, .y = 10 }),
				  	  Cell(Coordinates{ .x = 60, .y = 10 })
				  }),
		Tetromino(TetrominoType::Z,
				  std::array<Cell, 4>
				  {
				  	  Cell(Coordinates{ .x = 40, .y = 0 }),
				  	  Cell(Coordinates{ .x = 50, .y = 0 }),
				  	  Cell(Coordinates{ .x = 50, .y = 10 }),
				  	  Cell(Coordinates{ .x = 60, .y = 10 })
				  })
	};

	// ”правл€емое игроком тетрамино 
	Tetromino _activeTetromino = SelectRandomTetromino();

	bool _isReselectAvaliable = true;

	bool _isDropRequired = false;
public:
	GameScene() = default;
		
	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;
private:
	Tetromino SelectRandomTetromino();

	bool IsTetrominoShouldMove();

	/// <summary>
	/// ќпредел€ет состо€ние тетрамино, путем проверки дошла ли тетрамино
	/// до упавших тетрамино и если дошла, то требуетс€ ли очистить строки,
	/// низа игрового пол€, вверхней границы игрового пол€
	/// </summary>
	TetrominoState GetTetrominoState();
	
	/// <summary>
	/// ѕоиск заполненных строк
	/// </summary>
	/// <returns>¬озвращает массив индексов заполненных строк</returns>
	std::vector<int> FindFullRows();

	/// <summary>
	///  ќчищает заполненные строки
	/// </summary>
	/// <param name="removeRowsIndexes"> - массив индексов заполненных строк</param>
	void ClearRows(const std::vector<int>& removeRowsIndexes);

	void DisplayFallenTetrominos();

	/// <param name="cell">- клетка, дл€ которой требуетс€ найти индекс на поле _cells</param>
	/// <returns>¬озвращает  индекс клетки на поле _cells</returns>
	int GetIndexFrom(const Cell& cell);

	/// <summary>
	/// ѕолучить индекс нижний клетки относительно клетки в хранилище упавших тетрамино
	/// </summary>
	/// <param name="cell">- клетка игрового пол€</param>
	/// <returns>»ндекс нижней клетки</returns>
	int GetLowerIndexFrom(const Cell& cell);

	/// <summary>
	/// —охран€ет клетки упавшей тетерамино в массиве _cells
	/// </summary>
	/// <param name="cells">- клетки, которые требуетс€ сохранить</param>
	void AddCellsToDroppedCellsStorage(const std::array<Cell, 4>& cells);

	void OnKeyDown(const SDL_Event& e);

	void OnKeyHold(const SDL_Event& e);

	void OnQuit(const SDL_Event& e);

	void OnLeftKeyDown(const SDL_Event& e);

	void OnRightKeyDown(const SDL_Event& e);

	void OnDownKeyDown(const SDL_Event& e);
};