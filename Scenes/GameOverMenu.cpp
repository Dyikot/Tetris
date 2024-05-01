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
		case SDL_MOUSEBUTTONDOWN:
			if(e.button.x >= _retryButton.GetPosition().x &&
				e.button.x <= _retryButton.GetPosition().x + _retryButton.GetWight() &&
				e.button.y >= _retryButton.GetPosition().y &&
				e.button.y <= _retryButton.GetPosition().y + _retryButton.GetHeight())
			{
				Application::Current()->SetNextScene(new GameScene());
			}
			else if(e.button.x >= _exitButton.GetPosition().x &&
				e.button.x <= _exitButton.GetPosition().x + _exitButton.GetWight() &&
				e.button.y >= _exitButton.GetPosition().y &&
				e.button.y <= _exitButton.GetPosition().y + _exitButton.GetHeight())
			{
				Application::Current()->Shutdown();
			}
		default:
			break;
	}
}

void GameOverMenu::Process()
{}
