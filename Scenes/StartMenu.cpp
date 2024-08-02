#include "StartMenu.h"

StartMenu::StartMenu()
{
	_buttons = { &_startGameButton, &_exitButton };
}

void StartMenu::Show()
{
	_title.Show();
    _startGameButton.Show();
    _settingsButton.Show();
    _exitButton.Show();
}

void StartMenu::HandleEvent(const SDL_Event& e)
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

void StartMenu::Process()
{

}

void StartMenu::OnMouseDown(const SDL_Event& e)
{
	if(_startGameButton.IsInRange(e.button.x, e.button.y))
	{
		Application::Current()->SetNextScene(new GameScene());
	}
	else if(_exitButton.IsInRange(e.button.x, e.button.y))
	{
		Application::Current()->Shutdown();
	}
}

void StartMenu::OnQuit(const SDL_Event & e)
{
	Application::Current()->Shutdown();
}
