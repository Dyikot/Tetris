#include "StartMenu.h"

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
			if(_startGameButton.IsInRange({.x = e.button.x, .y = e.button.y }))
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

void StartMenu::Process()
{

}
