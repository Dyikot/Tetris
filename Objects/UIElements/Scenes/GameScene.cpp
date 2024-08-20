#include "GameScene.h"

GameScene::GameScene() noexcept
{
	Objects = { &_grid, &_cellStorage, &_activeTetromino };

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
	_activeTetromino.UpdatePlaceholderPosition();
	_activeTetromino.MovePlaceholderAtBottomOf(_cellStorage);

	if(_activeTetromino.IsLocatedAtBottomOf(_cellStorage))
	{
		_cellStorage.Add(_activeTetromino);

		if(_cellStorage.AreRowsFull(_activeTetromino))
		{
			_cellStorage.RowClearAnimation.Start();
		}

		_activeTetromino = _tetrominos.SelectRandom();
		_activeTetromino.CanReselected = true;

		if(_cellStorage.IsLocatedInCells(_activeTetromino))
		{
			Application::Current()->SetNextScene(new GameOverMenu());
			Close();
		}
	}
}

void GameScene::SetBackground()
{
	Colors::SetRenderColor(_renderer, Color::Black);
}

void GameScene::OnLeftKeyPressed()
{
	if(!_activeTetromino.IsOnLeftBorder(LeftBorder))
	{
		_activeTetromino.Move(MovementSide::Left);
	}
}

void GameScene::OnRightKeyPressed()
{
	if(!_activeTetromino.IsOnRightBorder(RightBorder))
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
			_activeTetromino.CorrectCoordinates(LeftBorder, RightBorder, TopBorder);
			break;

		case SDLK_SPACE:
			_activeTetromino.NeedsToFall = true;
			break;

		case SDLK_c:
			if(_activeTetromino.CanReselected)
			{
				_activeTetromino.CanReselected = false;
				_activeTetromino = _tetrominos.SelectRandom();
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