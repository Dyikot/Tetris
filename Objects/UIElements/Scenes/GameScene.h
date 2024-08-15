#pragma once

#include <iostream>
#include <ranges>

#include "IScene.h"
#include "MenuScenes/GameOverMenu.h"
#include "MenuScenes/PauseMenu.h"
#include "../../Application/Application.h"
#include "../../GameObjects/Cell.h"
#include "../../GameObjects/Grid.h"
#include "../../GameObjects/Tetromino.h"
#include "../../Events/HoldKeyEvent.h"
#include "../../Style/Texture.h"
#include "../../Style/Animation.h"
#include "Random/Random.h"

class GameScene: public Scene
{
private:
	static constexpr int HorizontalCellsNumber = 10;
	static constexpr int VerticalCellsNumber = 20;
	static constexpr int TicksAmountToTetrominoMove = 70;
	static constexpr int TicksAmountToClearCell = 8;
	static constexpr int CyclesToCompleteCellClearAnimation = HorizontalCellsNumber / 2;
	static constexpr int FieldWidth = HorizontalCellsNumber * Cell::Size;
	static constexpr int FieldHeight = VerticalCellsNumber * Cell::Size;
	
	Random _random;

	//  летки упавших тетрамино
	std::vector<std::vector<Cell>> _cellsStorage = std::vector<std::vector<Cell>>(
												VerticalCellsNumber,
												std::vector<Cell>(HorizontalCellsNumber));

	std::vector<int> _fullRowIndeces;

	Texture _cellTexture = Texture(Application::Current()->GetRenderer(),
								   "Resources/Textures/tile.png");

	// —етка пол€
	Grid _grid = Grid(/*position*/ { .x = 0, .y = 0 },
					  /*rowsAmount*/ VerticalCellsNumber,
					  /*columnsAmount*/ HorizontalCellsNumber,
					  /*width*/ FieldWidth * Scale,	
					  /*height*/ FieldHeight * Scale,
					  /*backgound*/ Color::Grey);

	// „исло пройденных циклов
	int _ticksAmount = 0;
	
	// “ипы тетрамино
	std::array<Tetromino, 7> _tetrominos = 
	{
		Tetromino(TetrominoType::I,
				  std::array<Cell, 4>
				  {
					  Cell(&_cellTexture, SDL_Point{ .x = 30, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 40, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 60, .y = 0 })
				  }),
		Tetromino(TetrominoType::J,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, SDL_Point{ .x = 40, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 40, .y = 10 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 10 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 60, .y = 10 })
				  }),
		Tetromino(TetrominoType::L,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, SDL_Point{ .x = 60, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 60, .y = 10 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 10 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 40, .y = 10 })
				  }),
		Tetromino(TetrominoType::O,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, SDL_Point{ .x = 40, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 40, .y = 10 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 10 })
				  }),
		Tetromino(TetrominoType::S,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 60, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 40, .y = 10 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 10 })
				  }),
		Tetromino(TetrominoType::T,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 40, .y = 10 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 10 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 60, .y = 10 })
				  }),
		Tetromino(TetrominoType::Z,
				  std::array<Cell, 4>
				  {
				  	  Cell(&_cellTexture, SDL_Point{ .x = 40, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 0 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 50, .y = 10 }),
					  Cell(&_cellTexture, SDL_Point{ .x = 60, .y = 10 })
				  })
	};

	// ”правл€емое игроком тетрамино 
	Tetromino _activeTetromino = SelectRandomTetromino();

	// Ќеактивное тетрамино, показывающее место расположени€ активного тетрамино в случае 
	// его падени€
	Tetromino _activeTetrominoPlaceHolder = GetCopyOfActiveTetrominoWith(Color::Grey);

	Animation _cellClearAnimation = Animation(TicksAmountToClearCell,
											  CyclesToCompleteCellClearAnimation);

	bool _isReselectAvaliable = true;

	bool _isDropRequired = false;
public:
	GameScene() noexcept;

	void Show() const override;

	void Process() override;

	void SetBackground() override;
private:
	/// <summary>
	/// ¬ыбирает из массива _tetrominos случаную тетрамино со случайным цветом
	/// </summary>
	/// <returns>—лучаную тетрамино со случаный цветом</returns>
	Tetromino SelectRandomTetromino();

	/// <summary>
	///  опирует активное тетрамино _activeTetromino с выбранным цветом
	/// </summary>
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
	/// ќтображает все упавшие тетрамино
	/// </summary>
	void ShowCellStorage() const;

	/// <summary>
	/// ¬озращает клетку из хранилища, исход€ от координат клетки cell
	/// </summary>
	/// <param name="cell"> - клетка активного тетрамино</param>
	/// <returns> летку в хранилище клеток упавших тетрамино</returns>
	Cell& GetCellAtStotage(const Cell& cell);

	/// <summary>
	/// ¬озращает клетку ниже уровнем из хранилища, исход€ от координат клетки cell
	/// </summary>
	/// <param name="cell"> - клетка, ниже клетки активного тетрамино</param>
	/// <returns> летку в хранилище клеток упавших тетрамино</returns>
	Cell& GetLowerCellAtStorage(const Cell& cell);

	/// <summary>
	/// ¬озращает индекс р€да из хранилища, исход€ от координат клетки cell
	/// </summary>
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

	void OnLeftKeyPressed();

	void OnRightKeyPressed();

	void OnDownKeyPressed();

	void OnKeyDown(Object* sender, const SDL_KeyboardEvent& e);

	void OnKeyHold(Object* sender, const SDL_KeyboardEvent& e);

	void OnCellClearAnimationCompleted(Animation* sender, const AnimationEventArgs& e);

	void OnCellClearAnimationCycleCompleted(Animation* sender, const AnimationEventArgs& e);
};