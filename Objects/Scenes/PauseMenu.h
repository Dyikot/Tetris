#pragma once

#include "IScene.h"
#include "../../Application/Application.h"
#include "../Controls/TextButton.h"
#include "../Controls/TextBlock.h"
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
	void OnKeyDown(Object* sender, const SDL_KeyboardEvent& e);

	void OnContinueButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnSettingsButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnExitButtonClick(Object* sender, const SDL_MouseButtonEvent& e);
};