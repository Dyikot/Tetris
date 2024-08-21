#pragma once

#include "../IScene.h"
#include "../GameScene.h"
#include "../../../../Application/Application.h"
#include "../../Controls/Buttons/TextButton.h"
#include "../../Controls/TextBlock.h"
#include "MenuScene.h"

class GameOverMenu: public MenuScene
{
private:
	// Main title

	TextBlock _title = TextBlock(MainTitlePosition,
								 Object::DefaultBackgroundColor,
								 "Game over",
								 Colors::Red,
								 Header1TextSize);

	// Retry button

	const SDL_Point RetryButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonVerticalPosition(/*order*/ 0)
	};
	TextButton _retryButton = TextButton(RetryButtonPosition,
										 DefaultButtonWidth,
										 DefaultButtonHeight,
										 Button::DefaultBackgroundColor,
										 Button::DefaultBorderColor,
										 "Retry",
										 TextBlock::ActiveTextColor,
										 TextButton::DefaultTextSize);

	// Exit button

	const SDL_Point ExitButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonVerticalPosition(/*order*/ 1)
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
	GameOverMenu();
private:
	void OnExitButtonClick(Object* sender, const SDL_MouseButtonEvent& e);

	void OnRetryButtonClick(Object* sender, const SDL_MouseButtonEvent& e);
};