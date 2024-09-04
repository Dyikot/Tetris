#pragma once

#include <algorithm>

#include "GameScene.h"
#include "SettingsMenu.h"
#include "../Controls/TextButton.h"
#include "../Controls/TextBlock.h"

class StartMenu : public MenuScene
{
private:
	GameAudioManager* _audioManager = Application::Current()->AudioManager<GameAudioManager>();
	
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
	void OnStartButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnSettingsButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnExitButtonClick(Object* sender, const SDL_MouseButtonEvent& e);
};