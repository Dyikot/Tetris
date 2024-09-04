#pragma once

#include <iostream>
#include <ranges>

#include "GameOverMenu.h"
#include "PauseMenu.h"
#include "../../Application/Window.h"
#include "../GameObjects/Cell.h"
#include "../GameObjects/Grid.h"
#include "../GameObjects/ActiveTetromino.h"
#include "../GameObjects/TetrominoCollection.h"
#include "../GameObjects/CellStorage.h"
#include "../../Graphics/Texture.h"
#include "../../Actions/Animation.h"
#include "../../Actions/Action.h"
#include "../../Audio/GameAudioManager.h"

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
	
	Texture _cellTexture = 
	{
		/*_renderer*/ Application::Current()->GetWindow()->Renderer,
		/*path*/ "Resources/Textures/tile.png"
	};
	GameAudioManager* _audioManager = Application::Current()->AudioManager<GameAudioManager>();
	CellStorage _cellStorage = 
	{
		/*columns*/ VerticalCellsNumber,
		/*rows*/ HorizontalCellsNumber,
		/*texture*/ &_cellTexture
	};
	Grid _grid = 
	{
		/*position*/ {.x = 0, .y = 0 },
		/*rows*/ VerticalCellsNumber,
		/*columns*/ HorizontalCellsNumber,
		/*width*/ FieldWidth * Scale,
		/*height*/ FieldHeight * Scale,
		/*lineColor*/ Colors::Darkgrey 
	};
	TetrominoCollection _tetrominos = TetrominoCollection(_cellTexture);
	ActiveTetromino _activeTetromino = _tetrominos.SelectRandom();
public:
	GameScene() noexcept;

	~GameScene();

	void Process() override;
private:
	void OnLeftKeyPressed();

	void OnRightKeyPressed();

	void OnDownKeyPressed();

	void OnVerticalMove();

	void OnKeyDown(Object* sender, const SDL_KeyboardEvent& e);

	void OnKeyHold(Object* sender, const SDL_KeyboardEvent& e);

	void OnHide(Object* sender, const EventArgs& e);

	void OnRowClearAnimationStarted(Animation* sender, const AnimationEventArgs& e);
};