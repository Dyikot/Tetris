#include "GameScene.h"

GameScene::GameScene() noexcept
{
	Objects = { &_grid, &_cellStorage, &_activeTetromino.PlaceHolder, &_activeTetromino };

	using namespace std::placeholders;
	
	KeyDown = std::bind(&GameScene::OnKeyDown, this, _1, _2);
	KeyHold = std::bind(&GameScene::OnKeyHold, this, _1, _2);
	Hidden = std::bind(&GameScene::OnHide, this, _1, _2);

	_activeTetromino.Movement.Start();
}

void GameScene::Process()
{
	if(_cellStorage.RowClearAnimation.TryProcess())
	{
		return;
	}

	_activeTetromino.Movement.TryProcess();

	_activeTetromino.UpdatePlaceHolder();

	while(!_cellStorage.IsLocatedAtBottom(_activeTetromino.PlaceHolder))
	{
		_activeTetromino.PlaceHolder.Move(MovementSide::Down);
	}

	switch(GetTetrominoState())
	{
		case TetrominoState::BeyoundUppedBorder:
			Application::Current()->SetNextScene(new GameOverMenu());
			break;

		case TetrominoState::Dropped:
			if(_cellStorage.AreFull(_cellStorage.GetLowestRowOf(_activeTetromino),
									_cellStorage.GetHighestRowOf(_activeTetromino)))
			{
				_cellStorage.RowClearAnimation.Start();
			}
			
			_activeTetromino = SelectRandomTetromino();
			_canReselectTetromino = true;

		case TetrominoState::Moving:
			break;
	}
}

void GameScene::SetBackground()
{
	Colors::SetRenderColor(_renderer, Color::Black);
}

Tetromino GameScene::SelectRandomTetromino()
{
	auto index = _random.NextInt(0, 6);
	auto color = Color(_random.NextInt(2, 8));

	auto tetromino = _tetrominos[index];
	tetromino.SetBackground(color);

	return tetromino;
}

TetrominoState GameScene::GetTetrominoState()
{
	// Проверка не появилась ли новая тетрамино в уже заполненном поле
	if(_activeTetromino.GetCells().front().Position.y <= Cell::Size)
	{
		bool isTetrominoInCells = std::ranges::any_of(_activeTetromino.GetCells(), 
			[this](const Cell& cell)
			{
				return _cellStorage.GetCellAt(cell).GetBackground() != Color::None;
			});

		if(isTetrominoInCells)
		{
			return TetrominoState::BeyoundUppedBorder;
		}
	}

	if(_isTetrominoNeedsDrop)
	{
		_isTetrominoNeedsDrop = false;
		_activeTetromino.CopyCoordinates(_activeTetromino.PlaceHolder);
		_cellStorage.Add(_activeTetromino);

		return TetrominoState::Dropped;
	}
	
	if(_cellStorage.IsLocatedAtBottom(_activeTetromino))
	{
		_cellStorage.Add(_activeTetromino);

		return TetrominoState::Dropped;
	}

	return TetrominoState::Moving;
}

void GameScene::OnLeftKeyPressed()
{
	if(!_activeTetromino.IsOutLeftBorder(0))
	{
		_activeTetromino.Move(MovementSide::Left);
	}
}

void GameScene::OnRightKeyPressed()
{
	if(!_activeTetromino.IsOutRightBorder(FieldWidth))
	{
		_activeTetromino.Move(MovementSide::Right);
	}
}

void GameScene::OnDownKeyPressed()
{
	_activeTetromino.Move(MovementSide::Down);
}

void GameScene::OnKeyDown(Object* sender, const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
		case SDLK_LEFT:
			OnLeftKeyPressed();
			break;

		case SDLK_RIGHT:
			OnRightKeyPressed();
			break;

		case SDLK_DOWN:
			OnDownKeyPressed();
			break;

		case SDLK_UP:
			_activeTetromino.Rotate();
			_activeTetromino.CorrectCoordinates(/*left*/ 0, /*right*/ FieldWidth, /*top*/ 0);
			break;

		case SDLK_SPACE:
			_isTetrominoNeedsDrop = true;
			break;

		case SDLK_c:
			if(_canReselectTetromino)
			{
				_activeTetromino = SelectRandomTetromino();
				_canReselectTetromino = false;
			}
			break;

		case SDLK_ESCAPE:
			Application::Current()->SetNextScene(new PauseMenu());
			Hide();
			break;

		default:
			break;
	}
}

void GameScene::OnKeyHold(Object* sender, const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
		case SDLK_LEFT:
			OnLeftKeyPressed();
			break;

		case SDLK_RIGHT:
			OnRightKeyPressed();
			break;

		case SDLK_DOWN:
			OnDownKeyPressed();
			break;

		default:
			break;
	}
}

void GameScene::OnHide(Object* sender, const EventArgs& e)
{
	_cellStorage.RowClearAnimation.Pause();
	_activeTetromino.Movement.Pause();
}