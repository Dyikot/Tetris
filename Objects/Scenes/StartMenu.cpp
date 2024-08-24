#include "StartMenu.h"

StartMenu::StartMenu()
{
	_navigationButtons = { &_startGameButton, &_settingsButton, &_exitButton };
	Objects = { &_title, &_startGameButton, &_settingsButton, &_exitButton };

	_title.SetText("Tetris");

	using namespace std::placeholders;

	_startGameButton.Click = std::bind(&StartMenu::OnStartButtonClick, this, _1, _2);
	_settingsButton.Click = std::bind(&StartMenu::OnSettingsButtonClick, this, _1, _2);
	_exitButton.Click = std::bind(&StartMenu::OnExitButtonClick, this, _1, _2);
}

void StartMenu::OnStartButtonClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->SetNextScene(new GameScene());
	Close();
}

void StartMenu::OnSettingsButtonClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->SetNextScene(new SettingsMenu());
	Hide();
}

void StartMenu::OnExitButtonClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	Close();
}
