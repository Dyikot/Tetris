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
			Application::Current()->Shutdown();
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(_startGameButton.IsInRange(e.button.x, e.button.y))
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

void StartMenu::Process()
{

}
