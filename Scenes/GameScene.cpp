#include "GameScene.h"

void GameScene::Show()
{
	_grid.Show();
	DisplayCellStorage();
	_activeTetrominoPlaceHolder.Show();
	_activeTetromino.Show();
}

void GameScene::HandleEvent(const SDL_Event& e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			OnQuit(e);
			break;

		case SDL_KEYDOWN:
			OnKeyDown(e);
			break;

		case SDL_KEYHOLD:
			OnKeyHold(e);
			break;

		default:
			break;
	}
}

void GameScene::Process()
{
	if(_cellClearAnimation.IsActivated())
	{
		_cellClearAnimation.Process();
		return;
	}

	if(IsTetrominoShouldMove())
	{
		_activeTetromino.Move(MovementSide::Down);
	}

	_activeTetrominoPlaceHolder = GetCopyOfActiveTetrominoWith(Color::Grey);

	while(!IsLocatedAtBottomOfStorage(_activeTetrominoPlaceHolder))
	{
		_activeTetrominoPlaceHolder.Move(MovementSide::Down);
	}

	switch(GetTetrominoState())
	{
		case TetrominoState::BeyoundUppedBorder:
			Application::Current()->SetNextScene(new GameOverMenu());
			break;

		case TetrominoState::Dropped:
			_fullRowIndeces = FindFullRows();

			if(_fullRowIndeces.size() > 0)
			{
				_cellClearAnimation.Start();
			}
			
			_activeTetromino = SelectRandomTetromino();
			_activeTetrominoPlaceHolder = GetCopyOfActiveTetrominoWith(Color::Grey);
			_isReselectAvaliable = true;

		case TetrominoState::Moving:
			break;
	}
}

void GameScene::OnCellClearAnimationCompleted()
{
	ClearRows(_fullRowIndeces);
}

void GameScene::OnCellClearAnimationCycleCompleted()
{
	const int CellToClearAmount = 2 * (_cellClearAnimation.GetCompletedCyclesAmount() + 1);
	const int StartColumn = HorizontalCellsNumber / 2
							   - _cellClearAnimation.GetCompletedCyclesAmount() - 1;
	const int EndColumn = HorizontalCellsNumber / 2
						  + _cellClearAnimation.GetCompletedCyclesAmount() + 1;

	for(int row: _fullRowIndeces)
	{
		for(int column = StartColumn; column < EndColumn; column++)
		{
			_cellsStorage[row][column].SetBackground(Color::None);
		}
	}
}

Tetromino GameScene::SelectRandomTetromino()
{
	auto tetrominoIndex = _random.NextInt(0, 6);
	auto color = Color(_random.NextInt(2, 8));

	auto tetromino = _tetrominos[tetrominoIndex];
	tetromino.SetBackground(color);

	return tetromino;
}

Tetromino GameScene::GetCopyOfActiveTetrominoWith(Color color)
{
	auto tetromino = _activeTetromino;
	tetromino.SetBackground(color);

	return tetromino;
}

bool GameScene::IsTetrominoShouldMove()
{
	_ticksAmount++;

	switch(_ticksAmount)
	{
		case TicksAmountToTetrominoMove:
			_ticksAmount = 0;
			return true;

		default:
			return false;
	}
}

TetrominoState GameScene::GetTetrominoState()
{
	// Проверка не появилась ли новая тетрамино в уже заполненном поле
	if(_activeTetromino.GetCells().front().StartPoint.y <= Cell::Size)
	{
		bool isTetrominoInCells = std::ranges::any_of(_activeTetromino.GetCells(), 
			[this](const Cell& cell)
			{
				return GetCellAtStotage(cell).GetBackground() != Color::None;
			});

		if(isTetrominoInCells)
		{
			return TetrominoState::BeyoundUppedBorder;
		}
	}

	if(_isDropRequired)
	{
		_isDropRequired = false;
		_activeTetromino.CopyCoordinates(_activeTetrominoPlaceHolder);
		AddCellsToDroppedCellsStorage(_activeTetromino.GetCells());

		return TetrominoState::Dropped;
	}
	
	if(IsLocatedAtBottomOfStorage(_activeTetromino))
	{
		AddCellsToDroppedCellsStorage(_activeTetromino.GetCells());
		return TetrominoState::Dropped;
	}

	return TetrominoState::Moving;
}

std::vector<int> GameScene::FindFullRows() const
{
	std::vector<int> fullRowsIndexes;
	int lowestRow = _activeTetromino.GetLowestCell().StartPoint.y / 10;
	int highestRow = _activeTetromino.GetHighestCell().StartPoint.y / 10;

	if(highestRow == 0)
	{
		int b = 0;
	}

	auto isRowFull = [&](int row)
	{
		return !std::ranges::any_of(_cellsStorage[row], [](const Cell& cell)
		{
			return cell.GetBackground() == Color::None;
		});
	};
	
 	for(int row = lowestRow; row >= highestRow; row--)
	{
		if(isRowFull(row))
		{
			fullRowsIndexes.push_back(row);
		}
	}

	return fullRowsIndexes;
}

void GameScene::ClearRows(const std::vector<int>& removeRowsIndexes)
{
	if(removeRowsIndexes.size() == 0)
	{
		return;
	}
	
	for(auto removeIndex : removeRowsIndexes)
	{
		_cellsStorage.erase(_cellsStorage.begin() + removeIndex);
	}
	
	_cellsStorage.insert(_cellsStorage.begin(),
						 removeRowsIndexes.size(),
						 std::vector(HorizontalCellsNumber, Cell(&_cellTexture)));
}

void GameScene::DisplayCellStorage()
{
	int cellsInRow = 1;

	for(int row = VerticalCellsNumber - 1; row >= 0; row--)
	{
		// Если строка пустая, то больше тетрамино не будет и можно выйти из цикла
		if(cellsInRow == 0)
		{
			break;
		}

		cellsInRow = 0;
		// Отображение упавший фигур
		for(int column = 0; column < HorizontalCellsNumber; column++)
		{
			if(_cellsStorage[row][column].GetBackground() != Color::None)
			{
				_cellsStorage[row][column].Show(
					{
						.x = column * Cell::Size,
						.y = row * Cell::Size
					});
				cellsInRow++;
			}
		}
	}
}

Cell& GameScene::GetCellAtStotage(const Cell& cell)
{
	return _cellsStorage[cell.StartPoint.y / Cell::Size][cell.StartPoint.x / Cell::Size];
}

Cell& GameScene::GetLowerCellAtStorage(const Cell& cell)
{
	return _cellsStorage[cell.StartPoint.y / Cell::Size + 1][cell.StartPoint.x / Cell::Size];
}

int GameScene::GetLowerCellRow(const Cell& cell) const
{
	return cell.StartPoint.y / Cell::Size + 1;
}

bool GameScene::IsLocatedAtBottomOfStorage(const Cell& cell)
{
	return GetLowerCellRow(cell) >= VerticalCellsNumber ||
		   GetLowerCellAtStorage(cell).GetBackground() != Color::None;
}

bool GameScene::IsLocatedAtBottomOfStorage(const Tetromino& tetromino)
{
	return std::ranges::any_of(tetromino.GetCells(), [this](const auto& cell)
	{
		return IsLocatedAtBottomOfStorage(cell);
	});
}

void GameScene::AddCellsToDroppedCellsStorage(const std::array<Cell, 4>& cells)
{	
	for(const auto& cell : cells)
	{
		GetCellAtStotage(cell) = cell;
	}
}

void GameScene::OnKeyDown(const SDL_Event& e)
{
	switch(e.key.keysym.sym)
	{
		case SDLK_LEFT:
			OnLeftKeyDown(e);
			break;

		case SDLK_RIGHT:
			OnRightKeyDown(e);
			break;

		case SDLK_DOWN:
			OnDownKeyDown(e);
			break;

		case SDLK_UP:
			_activeTetromino.Rotate();
			_activeTetromino.CorrectCoordinates(/*left*/ 0, /*right*/ FieldWidth, /*top*/ 0);
			break;

		case SDLK_SPACE:
			_isDropRequired = true;
			break;

		case SDLK_c:
			if(_isReselectAvaliable)
			{
				_activeTetromino = SelectRandomTetromino();
				_activeTetrominoPlaceHolder = GetCopyOfActiveTetrominoWith(Color::Grey);
				_isReselectAvaliable = false;
			}
			break;

		case SDLK_ESCAPE:
			Application::Current()->SaveCurrentScene();
			Application::Current()->SetNextScene(new PauseMenu());
			break;

		default:
			break;
	}
}

void GameScene::OnKeyHold(const SDL_Event& e)
{
	switch(e.key.keysym.sym)
	{
		case SDLK_LEFT:
			OnLeftKeyDown(e);
			break;

		case SDLK_RIGHT:
			OnRightKeyDown(e);
			break;

		case SDLK_DOWN:
			OnDownKeyDown(e);
			break;

		default:
			break;
	}
}

void GameScene::OnQuit(const SDL_Event & e)
{
	Application::Current()->Shutdown();
}

void GameScene::OnLeftKeyDown(const SDL_Event& e)
{
	if(!_activeTetromino.IsOutLeftBorder(0))
	{
		_activeTetromino.Move(MovementSide::Left);
	}
}

void GameScene::OnRightKeyDown(const SDL_Event & e)
{
	if(!_activeTetromino.IsOutRightBorder(FieldWidth))
	{
		_activeTetromino.Move(MovementSide::Right);
	}
}

void GameScene::OnDownKeyDown(const SDL_Event & e)
{
	_activeTetromino.Move(MovementSide::Down);
}