#pragma once

#include "../Scene.h"
#include "../../Application/Application.h"
#include "../../Objects/Controls/Buttons/TextButton.h"
#include "../../Objects/Controls/TextBlock.h"
#include "SettingsMenu.h"

class PauseMenu: public Scene, protected Menu
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

	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;

	void OnMouseDown(const SDL_Event& e);

	void OnQuit(const SDL_Event& e);

	void OnKeyDown(const SDL_Event& e);
};