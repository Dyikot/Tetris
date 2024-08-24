#pragma once

#include "IScene.h"
#include "GameScene.h"
#include "../../Application/Application.h"
#include "../Controls/TextButton.h"
#include "../Controls/TextBlock.h"
#include "MenuScene.h"

class GameOverMenu: public MenuScene
{
private:
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