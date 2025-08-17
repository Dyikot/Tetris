#include "StartMenu.h"
#include "../Application/Window.h"

StartMenu::StartMenu()
{
	_navigationButtons = { &_startGameButton, &_settingsButton, &_exitButton };
	Objects = { &_title, &_startGameButton, &_settingsButton, &_exitButton };

	_title.SetText("Tetris");
	
	_startGameButton.Click = std::bind_front(&StartMenu::OnStartButtonClick, this);
	_settingsButton.Click = std::bind_front(&StartMenu::OnSettingsButtonClick, this);
	_exitButton.Click = std::bind_front(&StartMenu::OnExitButtonClick, this);
}

void StartMenu::OnStartButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->GetWindow()->SetNextScene(new GameScene());
	Close();
}

void StartMenu::OnSettingsButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->GetWindow()->SetNextScene(new SettingsMenu());
	Hide();
}

void StartMenu::OnExitButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e)
{
	Close();
}