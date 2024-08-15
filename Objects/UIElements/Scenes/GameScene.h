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

	// ������ ������� ���������
	std::vector<std::vector<Cell>> _cellsStorage = std::vector<std::vector<Cell>>(
												VerticalCellsNumber,
												std::vector<Cell>(HorizontalCellsNumber));

	std::vector<int> _fullRowIndeces;

	Texture _cellTexture = Texture(Application::Current()->GetRenderer(),
								   "Resources/Textures/tile.png");

	// ����� ����
	Grid _grid = Grid(/*position*/ { .x = 0, .y = 0 },
					  /*rowsAmount*/ VerticalCellsNumber,
					  /*columnsAmount*/ HorizontalCellsNumber,
					  /*width*/ FieldWidth * Scale,	
					  /*height*/ FieldHeight * Scale,
					  /*backgound*/ Color::Grey);

	// ����� ���������� ������
	int _ticksAmount = 0;
	
	// ���� ���������
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

	// ����������� ������� ��������� 
	Tetromino _activeTetromino = SelectRandomTetromino();

	// ���������� ���������, ������������ ����� ������������ ��������� ��������� � ������ 
	// ��� �������
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
	/// �������� �� ������� _tetrominos �������� ��������� �� ��������� ������
	/// </summary>
	/// <returns>�������� ��������� �� �������� ������</returns>
	Tetromino SelectRandomTetromino();

	/// <summary>
	/// �������� �������� ��������� _activeTetromino � ��������� ������
	/// </summary>
	/// <param name="color">color - ���� ���������</param>
	/// <returns>����� ��������� ��������� _activeTetromino � ��������� ������</returns>
	Tetromino GetCopyOfActiveTetrominoWith(Color color);

	/// <summary>
	/// �������� ��������� ���������� ������ TicksAmountToTetrominoMove ����.
	/// ���������� �������� �� ���� ����.
	/// </summary>
	/// <returns>���� ��������, �� ��������� - true, ���� ��� - false</returns>
	bool IsTetrominoShouldMove();

	/// <summary>
	/// ���������� ��������� ���������, ����� �������� ����� �� ���������
	/// �� ������� ��������� � ���� �����, �� ��������� �� �������� ������,
	/// ���� �������� ����, �������� ������� �������� ����
	/// </summary>
	TetrominoState GetTetrominoState();
	
	/// <summary>
	/// ����� ����������� �����
	/// </summary>
	/// <returns>������ �������� ����������� �����</returns>
	std::vector<int> FindFullRows() const;

	/// <summary>
	///  ������� ����������� ������
	/// </summary>
	/// <param name="removeRowsIndexes"> - ������ �������� ����������� �����</param>
	void ClearRows(const std::vector<int>& removeRowsIndexes);

	/// <summary>
	/// ���������� ��� ������� ���������
	/// </summary>
	void ShowCellStorage() const;

	/// <summary>
	/// ��������� ������ �� ���������, ������ �� ��������� ������ cell
	/// </summary>
	/// <param name="cell"> - ������ ��������� ���������</param>
	/// <returns>������ � ��������� ������ ������� ���������</returns>
	Cell& GetCellAtStotage(const Cell& cell);

	/// <summary>
	/// ��������� ������ ���� ������� �� ���������, ������ �� ��������� ������ cell
	/// </summary>
	/// <param name="cell"> - ������, ���� ������ ��������� ���������</param>
	/// <returns>������ � ��������� ������ ������� ���������</returns>
	Cell& GetLowerCellAtStorage(const Cell& cell);

	/// <summary>
	/// ��������� ������ ���� �� ���������, ������ �� ��������� ������ cell
	/// </summary>
	/// <param name="cell"> - ������, ���� ������ ��������� ���������</param>
	/// <returns>��� � ��������� ������ ������� ���������</returns>
	int GetLowerCellRow(const Cell& cell) const;

	bool IsLocatedAtBottomOfStorage(const Cell& cell);

	bool IsLocatedAtBottomOfStorage(const Tetromino& tetromino);

	/// <summary>
	/// ��������� ������ ������� ���������� � ������� _cells
	/// </summary>
	/// <param name="cells">- ������, ������� ��������� ���������</param>
	void AddCellsToDroppedCellsStorage(const std::array<Cell, 4>& cells);

	void OnLeftKeyPressed();

	void OnRightKeyPressed();

	void OnDownKeyPressed();

	void OnKeyDown(Object* sender, const SDL_KeyboardEvent& e);

	void OnKeyHold(Object* sender, const SDL_KeyboardEvent& e);

	void OnCellClearAnimationCompleted(Animation* sender, const AnimationEventArgs& e);

	void OnCellClearAnimationCycleCompleted(Animation* sender, const AnimationEventArgs& e);
};