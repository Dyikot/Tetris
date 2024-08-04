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
			OnQuit(e);
			break;

		case SDL_MOUSEBUTTONDOWN:
			OnMouseDown(e);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(e);
			break;

		default:
			break;
	}
}

void GameOverMenu::Process()
{}

void GameOverMenu::OnMouseDown(const SDL_Event & e)
{
	if(_retryButton.IsInRange(e.button.x, e.button.y))
	{
		Application::Current()->SetNextScene(new GameScene());
	}
	else if(_exitButton.IsInRange(e.button.x, e.button.y))
	{
		Application::Current()->Shutdown();
	}
}

void GameOverMenu::OnQuit(const SDL_Event & e)
{
	Application::Current()->Shutdown();
}
