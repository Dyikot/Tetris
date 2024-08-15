#include "GameOverMenu.h"

GameOverMenu::GameOverMenu()
{
	NavigationButtons = { &_retryButton, &_exitButton };
	Objects = { &_title, &_retryButton, &_exitButton };

	using namespace std::placeholders;

	_retryButton.Click = std::bind(&GameOverMenu::OnRetryButtonClick, this, _1, _2);
	_exitButton.Click = std::bind(&GameOverMenu::OnExitButtonClick, this, _1, _2);
}

void GameOverMenu::OnRetryButtonClick(Object* sender, const SDL_MouseButtonEvent& e)
{
	Application::Current()->SetNextScene(new GameScene());
}

void GameOverMenu::OnExitButtonClick(Object * sender, const SDL_MouseButtonEvent& e)
{
	OnQuit({.type = SDL_QUIT, .timestamp = e.timestamp});
}
