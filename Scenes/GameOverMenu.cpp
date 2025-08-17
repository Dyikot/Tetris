#include "GameOverMenu.h"

GameOverMenu::GameOverMenu()
{
	_navigationButtons = { &_retryButton, &_exitButton };
	Objects = { &_title, &_retryButton, &_exitButton };

	_title.SetText("Game Over");
	_title.SetFontColor(Colors::Red);

	_audioManager->GetSoundEffect("GameOver").Play();

	_retryButton.Click = std::bind_front(&GameOverMenu::OnRetryButtonClick, this);
	_exitButton.Click = std::bind_front(&GameOverMenu::OnExitButtonClick, this);
}

void GameOverMenu::OnExitButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e)
{
	Close();
}

void GameOverMenu::OnRetryButtonClick(Renderable * sender, const SDL_MouseButtonEvent & e)
{
	Application::Current()->GetWindow()->SetNextScene(new GameScene());
	Close();
}