#pragma once

#include "GameScene.h"
#include "MenuScene.h"
#include "../Application/Window.h"
#include "../UI/Controls/TextButton.h"
#include "../UI/Controls/TextBlock.h"

class GameOverMenu: public MenuScene
{
private:
	AudioManager* _audioManager = Application::Current()->GetAudioManager();

	TextButton _retryButton =
	{
		SDL_Point
		{
			.x = NavigationButtonVerticalPosition,
			.y = CalculateButtonVerticalPosition(/*order*/ 0)
		},
		"Retry",
		NavigationButtonStyle
	};

	TextButton _exitButton =
	{
		SDL_Point
		{
			.x = NavigationButtonVerticalPosition,
			.y = CalculateButtonVerticalPosition(/*order*/ 1)
		},
		"Exit",
		NavigationButtonStyle
	};
public:
	GameOverMenu();
private:
	void OnExitButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnRetryButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
};