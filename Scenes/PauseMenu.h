#pragma once

#include "../UI/Controls/TextButton.h"
#include "../UI/Controls/TextBlock.h"
#include "SettingsMenu.h"

class PauseMenu: public MenuScene
{
private:
	TextButton _continueButton = 
	{
		SDL_Point
		{
			.x = NavigationButtonVerticalPosition,
			.y = CalculateButtonVerticalPosition(/*order*/ 0)
		},
		"Continue",
		NavigationButtonStyle
	};

	TextButton _settingsButton = 
	{
		SDL_Point
		{
			.x = NavigationButtonVerticalPosition,
			.y = CalculateButtonVerticalPosition(/*order*/ 1)
		},
		"Settings",
		NavigationButtonStyle 
	};

	TextButton _exitButton = 
	{
		SDL_Point
		{
			.x = NavigationButtonVerticalPosition,
			.y = CalculateButtonVerticalPosition(/*order*/ 2)
		},
		"Exit",
		NavigationButtonStyle 
	};
public:
	PauseMenu();
private:
	void OnKeyDown(Renderable* sender, const SDL_KeyboardEvent& e);
	void OnContinueButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnSettingsButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnExitButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
};