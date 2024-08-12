#include "StartMenu.h"

StartMenu::StartMenu()
{
	_buttons = { &_startGameButton, &_settingsButton, &_exitButton };
	_controls = { &_title, &_startGameButton, &_settingsButton, &_exitButton };
}

void StartMenu::Show()
{
	ShowControls();
}

void StartMenu::HandleEvent(const SDL_Event& e)
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

void StartMenu::Process()
{

}

void StartMenu::OnMouseDown(const SDL_Event& e)
{
	if(_hoverButton == &_startGameButton)
	{
		Application::Current()->SetNextScene(new GameScene());
	}
	else if(_hoverButton == &_settingsButton)
	{
		Application::Current()->SaveCurrentScene();
		Application::Current()->SetNextScene(new SettingsMenu());
	}
	else if(_hoverButton == &_exitButton)
	{
		Application::Current()->Shutdown();
	}
}

void StartMenu::OnQuit(const SDL_Event & e)
{
	Application::Current()->Shutdown();
}
