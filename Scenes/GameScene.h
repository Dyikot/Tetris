#pragma once

#include <iostream>
#include <ranges>

#include "Scene.h"
#include "MenuScenes/GameOverMenu.h"
#include "MenuScenes/PauseMenu.h"
#include "../Application/Application.h"
#include "../Objects/GameObjects/Cell.h"
#include "../Objects/GameObjects/Grid.h"
#include "../Objects/GameObjects/Tetromino.h"
#include "../Events/HoldKeyEvent.h"
#include "../Style/Texture.h"
#include "Random/Random.h"

class GameScene: public Scene
{
private:
	static constexpr int HorizontalCellsNumber = 10;
	static constexpr int VerticalCellsNumber = 20;
	static constexpr int TicksAmountToTetrominoMove = 70;
	static constexpr int FieldWidth = HorizontalCellsNumber * Cell::Size;
	static constexpr int FieldHeight = VerticalCellsNumber * Cell::Size;
	const int WidthScale = Application::Current()->WindowWidth / FieldWidth;
	const int HeightScale = Application::Current()->WindowHeight / FieldHeight;
	
	Random _random;

	//  летки упавших тетрамино
	std::vector<std::vector<Cell>> _cellsStorage = std::vector<std::vector<Cell>>(
												VerticalCellsNumber,
												std::vector<Cell>(HorizontalCellsNumber));

	std::vector<int> _fullRowIndeces;

	Texture _cellTexture = Texture(Application::Current()->GetRenderer(),
								   "Resources/Textures/tile.png");

	// —етка пол€
	Grid _grid = Grid(/*startPoint*/ { .x = 0, .y = 0 },
					  /*rowsAmount*/ VerticalCellsNumber,
					  /*columnsAmount*/ HorizontalCellsNumber,
					  /*width*/ FieldWidth * WidthScale,	
					  /*height*/ FieldHeight * HeightScale,
					  /*backgound*/ Color::Grey);

	// „исло пройденных циклов
	int _ticksAmount = 0;
	
	// “етрамино
	std::array<Tetromino, 7> _tetrominos = 
	{
		Tetromino(TetrominoType::I,
				  std::array<Cell, 4>
				  {
					  Cell(&_cellTexture, Coordinates{ .x = 30, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 40, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 60, .y = 0 })
				  }),
		Tetromino(TetrominoType::J,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, Coordinates{ .x = 40, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 40, .y = 10 }),
					  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 10 }),
					  Cell(&_cellTexture, Coordinates{ .x = 60, .y = 10 })
				  }),
		Tetromino(TetrominoType::L,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, Coordinates{ .x = 60, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 60, .y = 10 }),
					  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 10 }),
					  Cell(&_cellTexture, Coordinates{ .x = 40, .y = 10 })
				  }),
		Tetromino(TetrominoType::O,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, Coordinates{ .x = 40, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 40, .y = 10 }),
					  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 10 })
				  }),
		Tetromino(TetrominoType::S,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 60, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 40, .y = 10 }),
					  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 10 })
				  }),
		Tetromino(TetrominoType::T,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 40, .y = 10 }),
					  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 10 }),
					  Cell(&_cellTexture, Coordinates{ .x = 60, .y = 10 })
				  }),
		Tetromino(TetrominoType::Z,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, Coordinates{ .x = 40, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, Coordinates{ .x = 50, .y = 10 }),
					  Cell(&_cellTexture, Coordinates{ .x = 60, .y = 10 })
				  })
	};

	// ”правл€емое игроком тетрамино 
	Tetromino _activeTetromino = SelectRandomTetromino();

	// Ќеактивное тетрамино, показывающее место расположени€ активного тетрамино в случае 
	// его падени€
	Tetromino _activeTetrominoPlaceHolder = GetCopyOfActiveTetrominoWith(Color::Grey);

	bool _isReselectAvaliable = true;

	bool _isDropRequired = false;
public:		
	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;
private:
	/// <summary>
	/// ¬ыбирает из массива _tetrominos случаную тетрамино со случайным цветом
	/// </summary>
	/// <returns>—лучаную тетрамино со случаный цветом</returns>
	Tetromino SelectRandomTetromino();

	/// <param name="color">color - цвет тетрамино</param>
	/// <returns> опию активного тетрамино _activeTetromino с выбранным цветом</returns>
	Tetromino GetCopyOfActiveTetrominoWith(Color color);

	/// <summary>
	/// ƒвижение тетромино происходит каждый TicksAmountToTetrominoMove цикл.
	/// ќпредел€ет наступил ли этот цикл.
	/// </summary>
	/// <returns>≈сли наступил, то возращает - true, если нет - false</returns>
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
	/// <returns>ћассив индексов заполненных строк</returns>
	std::vector<int> FindFullRows() const;

	/// <summary>
	///  ќчищает заполненные строки
	/// </summary>
	/// <param name="removeRowsIndexes"> - массив индексов заполненных строк</param>
	void ClearRows(const std::vector<int>& removeRowsIndexes);

	/// <summary>
	/// ќтображает на игровом поле все упавшие тетрамино
	/// </summary>
	void DisplayCellStorage();

	/// <param name="cell"> - клетка активного тетрамино</param>
	/// <returns> летку в хранилище клеток упавших тетрамино</returns>
	Cell& GetCellAtStotage(const Cell& cell);

	/// <param name="cell"> - клетка, ниже клетки активного тетрамино</param>
	/// <returns> летку в хранилище клеток упавших тетрамино</returns>
	Cell& GetLowerCellAtStorage(const Cell& cell);

	/// <param name="cell"> - клетка, ниже клетки активного тетрамино</param>
	/// <returns>–€д в хранилище клеток упавших тетрамино</returns>
	int GetLowerCellRow(const Cell& cell) const;

	bool IsLocatedAtBottomOfStorage(const Cell& cell);

	bool IsLocatedAtBottomOfStorage(const Tetromino& tetromino);

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