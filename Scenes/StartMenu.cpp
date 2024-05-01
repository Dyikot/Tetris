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
		case SDL_MOUSEBUTTONDOWN:
			if(e.button.x >= _startGameButton.GetPosition().x &&
				e.button.x <= _startGameButton.GetPosition().x + _startGameButton.GetWight() &&
				e.button.y >= _startGameButton.GetPosition().y &&
				e.button.y <= _startGameButton.GetPosition().y + _startGameButton.GetHeight())
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

void StartMenu::Process()
{

}
