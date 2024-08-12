#pragma once

#include "../Scene.h"
#include "../GameScene.h"
#include "../../Application/Application.h"
#include "../../Objects/Controls/Buttons/TextButton.h"
#include "../../Objects/Controls/TextBlock.h"
#include "Menu.h"

class GameOverMenu: public Scene, protected Menu
{
private:
	// Main title

	TextBlock _title = TextBlock(MainTitlePosition,
								 Object::DefaultBackgroundColor,
								 "Game over",
								 Color::Red,
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

	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;

	void OnMouseDown(const SDL_Event& e);

	void OnQuit(const SDL_Event& e);
};