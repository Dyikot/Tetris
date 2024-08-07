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

	// ������ ������� ���������
	std::vector<std::vector<Cell>> _cellsStorage = std::vector<std::vector<Cell>>(
												VerticalCellsNumber,
												std::vector<Cell>(HorizontalCellsNumber));

	std::vector<int> _fullRowIndeces;

	Texture _cellTexture = Texture(Application::Current()->GetRenderer(),
								   "Resources/Textures/tile.png");

	// ����� ����
	Grid _grid = Grid(/*startPoint*/ { .x = 0, .y = 0 },
					  /*rowsAmount*/ VerticalCellsNumber,
					  /*columnsAmount*/ HorizontalCellsNumber,
					  /*width*/ FieldWidth * WidthScale,	
					  /*height*/ FieldHeight * HeightScale,
					  /*backgound*/ Color::Grey);

	// ����� ���������� ������
	int _ticksAmount = 0;
	
	// ���������
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

	// ����������� ������� ��������� 
	Tetromino _activeTetromino = SelectRandomTetromino();

	// ���������� ���������, ������������ ����� ������������ ��������� ��������� � ������ 
	// ��� �������
	Tetromino _activeTetrominoPlaceHolder = GetCopyOfActiveTetrominoWith(Color::Grey);

	bool _isReselectAvaliable = true;

	bool _isDropRequired = false;
public:		
	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;
private:
	/// <summary>
	/// �������� �� ������� _tetrominos �������� ��������� �� ��������� ������
	/// </summary>
	/// <returns>�������� ��������� �� �������� ������</returns>
	Tetromino SelectRandomTetromino();

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
	/// ���������� �� ������� ���� ��� ������� ���������
	/// </summary>
	void DisplayCellStorage();

	/// <param name="cell"> - ������ ��������� ���������</param>
	/// <returns>������ � ��������� ������ ������� ���������</returns>
	Cell& GetCellAtStotage(const Cell& cell);

	/// <param name="cell"> - ������, ���� ������ ��������� ���������</param>
	/// <returns>������ � ��������� ������ ������� ���������</returns>
	Cell& GetLowerCellAtStorage(const Cell& cell);

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

	void OnKeyDown(const SDL_Event& e);

	void OnKeyHold(const SDL_Event& e);

	void OnQuit(const SDL_Event& e);

	void OnLeftKeyDown(const SDL_Event& e);

	void OnRightKeyDown(const SDL_Event& e);

	void OnDownKeyDown(const SDL_Event& e);
};