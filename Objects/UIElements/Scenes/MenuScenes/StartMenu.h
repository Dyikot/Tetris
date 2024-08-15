#pragma once

#include <algorithm>

#include "../IScene.h"
#include "../GameScene.h"
#include "SettingsMenu.h"
#include "../../Controls/Buttons/TextButton.h"
#include "../../Controls/TextBlock.h"

class StartMenu : public MenuScene
{
private:	
	// Main title

	TextBlock _title = TextBlock(MainTitlePosition,
							     Object::DefaultBackgroundColor,
							     "Tetris",
							     TextBlock::ActiveTextColor,
							     Header1TextSize);

	// Start game button

	const SDL_Point StartGameButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonVerticalPosition(/*order*/ 0)
	};

	TextButton _startGameButton = TextButton(StartGameButtonPosition,
											 DefaultButtonWidth,
											 DefaultButtonHeight,
											 Button::DefaultBackgroundColor,
											 Button::DefaultBorderColor,
											 "Play",
											 TextBlock::ActiveTextColor,
											 TextButton::DefaultTextSize);

	// Settings button

	const SDL_Point SettingsButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonVerticalPosition(/*order*/ 1)
	};

	TextButton _settingsButton = TextButton(SettingsButtonPosition,
											DefaultButtonWidth,
											DefaultButtonHeight,
											Button::DefaultBackgroundColor,
											Button::DefaultBorderColor,
											"Settings",
											TextBlock::ActiveTextColor,
											TextButton::DefaultTextSize);

	// Exit button

	const SDL_Point ExitButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonVerticalPosition(/*order*/ 2)
	};

	TextButton _exitButton = TextButton(ExitButtonPosition,
										DefaultButtonWidth,
										DefaultButtonHeight,
										Button::DefaultBackgroundColor,
										Button::DefaultBorderColor,
										"Exit",
										TextBlock::ActiveTextColor,
										TextButton::DefaultTextSize);
public:
	StartMenu();
private:
	void OnStartButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnSettingsButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnExitButtonClick(Object* sender, const SDL_MouseButtonEvent& e);
};