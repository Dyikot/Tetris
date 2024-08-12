#pragma once

#include <algorithm>

#include "../Scene.h"
#include "../GameScene.h"
#include "SettingsMenu.h"
#include "../../Objects/Controls/Buttons/TextButton.h"
#include "../../Objects/Controls/TextBlock.h"

class StartMenu : public Scene, protected Menu
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

	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;

	void OnMouseDown(const SDL_Event& e);

	void OnQuit(const SDL_Event& e);
};