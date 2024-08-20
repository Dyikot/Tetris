#pragma once

#include <iostream>
#include <ranges>

#include "IScene.h"
#include "MenuScenes/GameOverMenu.h"
#include "MenuScenes/PauseMenu.h"
#include "../../../Application/Application.h"
#include "../../GameObjects/Cell.h"
#include "../../GameObjects/Grid.h"
#include "../../GameObjects/Tetromino/ActiveTetromino.h"
#include "../../GameObjects/CellStorage.h"
#include "../../../Events/HoldKeyEvent.h"
#include "../../../Style/Texture.h"
#include "../../../Tools/Actions/Animation.h"
#include "../../../Tools/Actions/Action.h"
#include "Random/Random.h"

class GameScene: public Scene
{
private:
	static constexpr int HorizontalCellsNumber = 10;
	static constexpr int VerticalCellsNumber = 20;
	static constexpr int FieldWidth = HorizontalCellsNumber * Cell::Size;
	static constexpr int FieldHeight = VerticalCellsNumber * Cell::Size;
	static constexpr int LeftBorder = 0;
	static constexpr int RightBorder = LeftBorder + FieldWidth;
	static constexpr int TopBorder = 0;
	static constexpr int BottomBorder = TopBorder + FieldHeight;
	static constexpr int ActionsForCellClearAnimation = HorizontalCellsNumber / 2;
	
	Random _random;
	Texture _cellTexture = Texture(Application::Current()->GetRenderer(),
								   "Resources/Textures/tile.png");
	/// <summary>
	/// Клетки упавших тетрамино
	/// </summary>
	CellStorage _cellStorage = CellStorage(VerticalCellsNumber,
										   HorizontalCellsNumber,
										   &_cellTexture);
	/// <summary>
	/// Сетка поля
	/// </summary>
	Grid _grid = Grid(/*position*/ { .x = 0, .y = 0 },
					  /*rows*/ VerticalCellsNumber,
					  /*columns*/ HorizontalCellsNumber,
					  /*width*/ FieldWidth * Scale,	
					  /*height*/ FieldHeight * Scale,
					  /*backgound*/ Color::Darkgrey);	
	/// <summary>
	/// Типы тетрамино
	/// </summary>
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
	/// <summary>
	/// Управляемое игроком тетрамино
	/// </summary>
	ActiveTetromino _activeTetromino = SelectRandomTetromino();
public:
	GameScene() noexcept;

	void Process() override;

	void SetBackground() override;
private:
	/// <summary>
	/// Выбирает из массива _tetrominos случаную тетрамино со случайным цветом
	/// </summary>
	/// <returns>Случаную тетрамино со случаный цветом</returns>
	Tetromino SelectRandomTetromino();

	bool HasActiveTetrominoFallen();

	void OnLeftKeyPressed();

	void OnRightKeyPressed();

	void OnDownKeyPressed();

	void OnKeyDown(Object* sender, const SDL_KeyboardEvent& e);

	void OnKeyHold(Object* sender, const SDL_KeyboardEvent& e);

	void OnHide(Object* sender, const EventArgs& e);
};