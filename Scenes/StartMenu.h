#pragma once

#include <algorithm>

#include "GameScene.h"
#include "SettingsMenu.h"
#include "../UI/Controls/TextButton.h"
#include "../UI/Controls/TextBlock.h"

class StartMenu : public MenuScene
{
private:
	AudioManager* _audioManager = Application::Current()->GetAudioManager();
	
	TextButton _startGameButton = 
	{
		SDL_Point
		{
			.x = NavigationButtonVerticalPosition,
			.y = CalculateButtonVerticalPosition(/*order*/ 0)
		},
		"Play",
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
	StartMenu();
private:
	void OnStartButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnSettingsButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
	void OnExitButtonClick(Renderable* sender, const SDL_MouseButtonEvent& e);
};