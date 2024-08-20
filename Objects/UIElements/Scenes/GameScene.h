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
#include "../../GameObjects/Tetromino/TetrominoCollection.h"
#include "../../GameObjects/CellStorage.h"
#include "../../../Events/HoldKeyEvent.h"
#include "../../../Style/Texture.h"
#include "../../../Tools/Actions/Animation.h"
#include "../../../Tools/Actions/Action.h"

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
	/// Коллекция всех видов тетрамино
	/// </summary>
	TetrominoCollection _tetrominos = TetrominoCollection(&_cellTexture);
	/// <summary>
	/// Управляемое игроком тетрамино
	/// </summary>
	ActiveTetromino _activeTetromino = _tetrominos.SelectRandom();
public:
	GameScene() noexcept;

	void Process() override;

	void SetBackground() override;
private:
	void OnLeftKeyPressed();

	void OnRightKeyPressed();

	void OnDownKeyPressed();

	void OnKeyDown(Object* sender, const SDL_KeyboardEvent& e);

	void OnKeyHold(Object* sender, const SDL_KeyboardEvent& e);

	void OnHide(Object* sender, const EventArgs& e);
};