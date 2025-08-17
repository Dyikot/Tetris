#include "GameScene.h"

GameScene::GameScene() noexcept
{
	Objects = { &_grid, &_cellStorage, &_activeTetromino };

	KeyDown = std::bind_front(&GameScene::OnKeyDown, this);
	KeyHold = std::bind_front(&GameScene::OnKeyHold, this);
	Hidden = std::bind_front(&GameScene::OnHide, this);
	_cellStorage.RowClearAnimation.AnimationStarted = std::bind_front(
		&GameScene::OnRowClearAnimationStarted, this);

	_audioManager->ShuffleMusicTracks();
	_activeTetromino.Movement.Start();
}

GameScene::~GameScene()
{
	_audioManager->CurrentTrack()->Stop();
}

void GameScene::Process()
{
	_audioManager->PlayMusic();

	if(_cellStorage.RowClearAnimation.TryProcess())
	{
		return;
	}

	_activeTetromino.Movement.TryProcess();
	_activeTetromino.UpdatePlaceholderPositionIn(_cellStorage);

	if(_activeTetromino.IsLocatedAtBottomOf(_cellStorage))
	{
		_cellStorage.Add(_activeTetromino);

		if(_cellStorage.AreRowsFull())
		{
			_cellStorage.RowClearAnimation.Start();
		}

		_activeTetromino = _tetrominoFactory.Create();
		_activeTetromino.CanReselected = true;

		if(_cellStorage.IsLocatedInCells(_activeTetromino))
		{
			Application::Current()->GetWindow()->SetNextScene(new GameOverMenu());
			Close();
		}
	}
}

void GameScene::OnLeftKeyPressed()
{
	if(!_activeTetromino.IsOnLeftBorder(LeftBorder))
	{
		_activeTetromino.Move(MovementSide::Left);
		OnVerticalMove();
	}
}

void GameScene::OnRightKeyPressed()
{
	if(!_activeTetromino.IsOnRightBorder(RightBorder))
	{
		_activeTetromino.Move(MovementSide::Right);
		OnVerticalMove();
	}
}

void GameScene::OnDownKeyPressed()
{
	_activeTetromino.Move(MovementSide::Down);
}

void GameScene::OnVerticalMove()
{
	_audioManager->GetSoundEffect("TetrominoMove").Play();
}

void GameScene::OnKeyDown(Renderable* sender, const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
		case SDLK_LEFT:
		{
			OnLeftKeyPressed();
			break;
		}

		case SDLK_RIGHT:
		{
			OnRightKeyPressed();
			break;
		}

		case SDLK_DOWN:
		{
			OnDownKeyPressed();
			break;
		}

		case SDLK_UP:
		{
			_activeTetromino.Rotate();
			_activeTetromino.CorrectCoordinates(LeftBorder, RightBorder, TopBorder);
			break;
		}

		case SDLK_SPACE:
		{
			_activeTetromino.NeedsToFall = true;
			_audioManager->GetSoundEffect("TetrominoFall").Play(/*channel*/ 1);
			break;
		}

		case SDLK_c:
		{
			if(_activeTetromino.CanReselected)
			{
				_activeTetromino.CanReselected = false;
				_activeTetromino = _tetrominoFactory.Create();
			}

			break;
		}

		case SDLK_ESCAPE:
		{
			Application::Current()->GetWindow()->SetNextScene(new PauseMenu());
			Hide();
			break;
		}
	}
}

void GameScene::OnKeyHold(Renderable* sender, const SDL_KeyboardEvent& e)
{
	switch(e.keysym.sym)
	{
		case SDLK_LEFT:
		{
			OnLeftKeyPressed();
			break;
		}

		case SDLK_RIGHT:
		{
			OnRightKeyPressed();
			break;
		}

		case SDLK_DOWN:
		{
			OnDownKeyPressed();
			break;
		}
	}
}

void GameScene::OnHide(Renderable* sender, const EventArgs& e)
{
	_audioManager->CurrentTrack()->Pause();
	_cellStorage.RowClearAnimation.Pause();
	_activeTetromino.Movement.Pause();
}

void GameScene::OnRowClearAnimationStarted(Animation* sender, 
												 const AnimationEventArgs& e)
{
	auto rows = _cellStorage.GetFullRowsIndices().size();

	switch(rows)
	{
		case 1:
		{
			_audioManager->GetSoundEffect("SingleRowClear").Play(/*channel*/ 1);
			break;
		}

		case 2:
		case 3:
		{
			_audioManager->GetSoundEffect("UpTo3RowClear").Play(/*channel*/ 1);
			break;
		}

		case 4:
		{
			_audioManager->GetSoundEffect("UpTo4RowClear").Play(/*channel*/ 1);
			break;
		}
	}
}