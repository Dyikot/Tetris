#include "GameOverMenu.h"

GameOverMenu::GameOverMenu()
{
	_buttons = { &_retryButton, &_exitButton };
	_controls = { &_title, &_retryButton, &_exitButton };
}

void GameOverMenu::Show()
{
	ShowControls();
}

void GameOverMenu::HandleEvent(const SDL_Event& e)
{
	switch(e.type)
	{
		case SDL_QUIT:
			OnQuit(e);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(_hoverButton == nullptr)
			{
				break;
			}

			OnMouseDown(e);
			Menu::OnMouseDown(e);
			break;

		case SDL_MOUSEMOTION:
			OnMouseMove(e);
			break;

		default:
			break;
	}
}

void GameOverMenu::Process()
{

}

void GameOverMenu::OnMouseDown(const SDL_Event & e)
{
	if(_hoverButton == &_retryButton)
	{
		Application::Current()->SetNextScene(new GameScene());
	}
	else if(_hoverButton == &_exitButton)
	{
		Application::Current()->Shutdown();
	}
}

void GameOverMenu::OnQuit(const SDL_Event & e)
{
	Application::Current()->Shutdown();
}
