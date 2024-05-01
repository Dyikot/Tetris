#include "GameScene.h"

void GameScene::Show()
{
	_grid.Show();
	ShowDroppedTetrominoes();
	_activeTetromino.Show();
}

void GameScene::HandleEvent(const SDL_Event& e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			Application::Current()->Shutdown();
			break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_LEFT:					
					if(!_activeTetromino.IsOutLeftBorder(/*left*/ 0))
					{
						_activeTetromino.Move(MovementSide::Left);
					}					
					break;
				case SDLK_RIGHT:
					if(!_activeTetromino.IsOutRightBorder(FieldWidth))
					{
						_activeTetromino.Move(MovementSide::Right);
					}
					break;
				case SDLK_DOWN:
					_activeTetromino.Move(MovementSide::Down);
					break;
				case SDLK_UP:
					_activeTetromino.Rotate();
					_activeTetromino.CorrectCoordinates(
						/*left*/ 0,
						/*right*/ FieldWidth,
						/*top*/ 0
					);
					break;
				case SDLK_SPACE:
					_isDropRequired = true;
					break;
				case SDLK_c:
					if(_isReselectAvaliable)
					{
						_activeTetromino = SelectTetriminoRandomly();
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
			break;
		default:
			break;
	}
}

void GameScene::Process()
{
	if(IsTetrominoShouldMove())
	{
		_activeTetromino.Move(MovementSide::Down);
	}

	switch(GetTetrominoState())
	{
		case TetrominoState::BeyoundUppedBorder:
			Application::Current()->SetNextScene(new GameOverMenu());
		case TetrominoState::Dropped:
			ClearRows(FindFullRows());
			_activeTetromino = SelectTetriminoRandomly();
			_isReselectAvaliable = true;
		case TetrominoState::Moving:
			break;
	}
}

Tetromino GameScene::SelectTetriminoRandomly() const
{
	auto tetromino = _tetrominos[Random::Current().GenerateNumber(0, 6)];
	tetromino.SetBackground(Colors(Random::Current().GenerateNumber(2, 7)));

	return tetromino;
}

bool GameScene::IsTetrominoShouldMove()
{
	_cyclesCompleted++;
	if(_cyclesCompleted == CyclesAmountToTetrominoMove)
	{
		_cyclesCompleted = 0;
		return true;
	}

	return false;
}

TetrominoState GameScene::GetTetrominoState()
{
	const auto& tetrominoCells = _activeTetromino.GetCells();
	int index;

	// ѕроверка не пов€илась ли нова€ тетрамино в уже заполненном поле
	if(GetIndexFrom(tetrominoCells.front()) < 20)
	{
		for(const auto& cell : tetrominoCells)
		{
			index = GetIndexFrom(cell);
			if(_cells[index].GetBackground() != Colors::None)
			{
				return TetrominoState::BeyoundUppedBorder;
			}
		}
	}
	// ѕроверка на наличие тетронимо ниже текущего
	// \return ¬озвращает  TetrominoState::Dropped, если ниже есть клетка,
	// если нет, то TetrominoState::Moving
	auto GetStateBasedOnLowerCells = [&]()
	{
		for(const auto& cell : tetrominoCells)
		{
			index = GetLowerIndexFrom(cell);
			// ѕроверка на то, достигла ли тетронимо нижней границы пол€
			if(index >= FieldHeight || _cells[index].GetBackground() != Colors::None)
			{
				AddCellsToDroppedCellsStorage(tetrominoCells);
				return TetrominoState::Dropped;
			}
		}

		return TetrominoState::Moving;
	};
	
	if(_isDropRequired)
	{
		_isDropRequired = false;
		while(GetStateBasedOnLowerCells() == TetrominoState::Moving)
		{
			_activeTetromino.Move(MovementSide::Down);
		}

		return TetrominoState::Dropped;
	}

	return GetStateBasedOnLowerCells();
}

std::vector<int> GameScene::FindFullRows()
{
	std::vector<int> removeRowsIndexes;
	int index = 0;
	int lastRow = _activeTetromino.GetHighestCoordinates().y / 10;

	for(int row = _activeTetromino.GetLowestCoordinates().y / 10; row >= lastRow; row--)
	{
		for(int column = 0; column < HorizontalCellsNumber; column++)
		{
			index = row * HorizontalCellsNumber + column;

			if(_cells[index].GetBackground() == Colors::None)
			{
				break;
			}
			else if(column + 1 == HorizontalCellsNumber)
			{
				removeRowsIndexes.push_back(row);
			}
		}
	}

	return removeRowsIndexes;
}

void GameScene::ClearRows(const std::vector<int>& removeRowsIndexes)
{
	if(removeRowsIndexes.size() == 0)
	{
		return;
	}

	for(auto removeIndex : removeRowsIndexes)
	{
		_cells.erase(
			_cells.begin() + removeIndex * HorizontalCellsNumber,
			_cells.begin() + removeIndex * HorizontalCellsNumber
			+ HorizontalCellsNumber
		);
	}

	_cells.insert(
		_cells.begin(),
		removeRowsIndexes.size() * HorizontalCellsNumber,
		Cell()
	);
}

void GameScene::ShowDroppedTetrominoes()
{
	int index = 0;
	int cellInRow = 1;

	for(int row = VerticalCellsNumber - 1; row >= 0; row--)
	{
		// ≈сли строка пуста€, то больше тетрамино не будет и можно выйти из цикла
		if(cellInRow == 0)
		{
			break;
		}

		cellInRow = 0;
		// ќтображение упавший фигур
		for(int column = 0; column < HorizontalCellsNumber; column++)
		{
			index = row * HorizontalCellsNumber + column;

			if(_cells[index].GetBackground() != Colors::None)
			{
				_cells[index].Show({ .x = column * Cell::Size, .y = row * Cell::Size });
				cellInRow++;
			}
		}
	}
}

int GameScene::GetIndexFrom(const Cell& cell)
{
	return cell.StartPoint.y / 10 * HorizontalCellsNumber + cell.StartPoint.x / 10;
}

int GameScene::GetLowerIndexFrom(const Cell& cell)
{
	return (cell.StartPoint.y / 10 + 1) * HorizontalCellsNumber + cell.StartPoint.x / 10;
}

void GameScene::AddCellsToDroppedCellsStorage(const std::array<Cell, 4>& cells)
{
	for(const auto& cell : cells)
	{
		_cells[GetIndexFrom(cell)] = cell;
	}
}
