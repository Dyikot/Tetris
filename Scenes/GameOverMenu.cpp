#include "GameOverMenu.h"

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
			if(_retryButton.IsInRange({ .x = e.button.x, .y = e.button.y }))
			{
				Application::Current()->SetNextScene(new GameScene());
			}
			else if(_exitButton.IsInRange({ .x = e.button.x, .y = e.button.y }))
			{
				Application::Current()->Shutdown();
			}
			break;

		default:
			break;
	}
}

void GameOverMenu::Process()
{}
