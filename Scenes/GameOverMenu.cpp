#include "GameOverMenu.h"

GameOverMenu::GameOverMenu()
{
	_buttons = { &_retryButton, &_exitButton };
}

void GameOverMenu::Show()
{
	_gameOverTextBlock.Show();
	_retryButton.Show();
	_exitButton.Show();
}

void GameOverMenu::HandleEvent(const SDL_Event& e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			Application::Current()->Shutdown();
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(_retryButton.IsInRange(e.button.x, e.button.y))
			{
				Application::Current()->SetNextScene(new GameScene());
			}
			else if(_exitButton.IsInRange(e.button.x, e.button.y))
			{
				Application::Current()->Shutdown();
			}
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(e.button.x, e.button.y);
			break;

		default:
			break;
	}
}

void GameOverMenu::Process()
{}
