#pragma once

#include "GameScene.h"
#include "../../Application/Window.h"
#include "../Controls/TextButton.h"
#include "../Controls/TextBlock.h"
#include "MenuScene.h"

class GameOverMenu: public MenuScene
{
private:
	GameAudioManager* _audioManager = Application::Current()->AudioManager<GameAudioManager>();

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
	void OnExitButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnRetryButtonClick(Object* sender, const SDL_MouseButtonEvent& e);
};