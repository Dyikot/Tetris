#pragma once

#include "../IScene.h"
#include "../../Application/Application.h"
#include "../../Controls/Buttons/TextButton.h"
#include "../../Controls/TextBlock.h"
#include "SettingsMenu.h"

class PauseMenu: public MenuScene
{
private:
	// Main title

	TextBlock _title = TextBlock(MainTitlePosition,
								 Object::DefaultBackgroundColor,
								 "Pause",
								 TextBlock::ActiveTextColor,
								 Header1TextSize);

	// Continue button
	
	const SDL_Point ContinueButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonVerticalPosition(/*order*/ 0)
	};
	TextButton _continueButton = TextButton(ContinueButtonPosition,
											DefaultButtonWidth,
											DefaultButtonHeight,
											Button::DefaultBackgroundColor,
											Button::DefaultBorderColor,
											"Continue",
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
	PauseMenu();
private:
	void OnKeyDown(Object* sender, const SDL_KeyboardEvent& e);

	void OnContinueButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnSettingsButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnExitButtonClick(Object* sender, const SDL_MouseButtonEvent& e);
};