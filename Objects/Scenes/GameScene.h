#pragma once

#include <iostream>
#include <ranges>

#include "IScene.h"
#include "GameOverMenu.h"
#include "PauseMenu.h"
#include "../../Application/Application.h"
#include "../GameObjects/Cell.h"
#include "../GameObjects/Grid.h"
#include "../GameObjects/ActiveTetromino.h"
#include "../GameObjects/TetrominoCollection.h"
#include "../GameObjects/CellStorage.h"
#include "../../Graphics/Texture.h"
#include "../../Actions/Animation.h"
#include "../../Actions/Action.h"

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
	/// ������ ������� ���������
	/// </summary>
	CellStorage _cellStorage = 
	{
		VerticalCellsNumber,
		HorizontalCellsNumber,
		&_cellTexture 
	};
	/// <summary>
	/// ����� ����
	/// </summary>
	Grid _grid = 
	{
		/*position*/ {.x = 0, .y = 0 },
		/*rows*/ VerticalCellsNumber,
		/*columns*/ HorizontalCellsNumber,
		/*width*/ FieldWidth * Scale,
		/*height*/ FieldHeight * Scale,
		/*lineColor*/ Colors::Darkgrey 
	};
	/// <summary>
	/// ��������� ���� ����� ���������
	/// </summary>
	TetrominoCollection _tetrominos = TetrominoCollection(_cellTexture);
	/// <summary>
	/// ����������� ������� ���������
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