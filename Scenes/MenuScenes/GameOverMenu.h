#pragma once

#include "../Scene.h"
#include "../GameScene.h"
#include "../../Application/Application.h"
#include "../../Objects/Controls/Button.h"
#include "../../Objects/Controls/TextBlock.h"
#include "Menu.h"

class GameOverMenu: public Scene, protected Menu
{
private:
	const int RetryButtonOrder = 0;
	const SDL_Point RetryButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonYPosition(RetryButtonOrder)
	};

	const int ExitButtonOrder = 1;
	const SDL_Point ExitButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonYPosition(ExitButtonOrder)
	};

	TextBlock _gameOverTextBlock = TextBlock(DefaultTitlePosition,
											 Object::DefaultBackgroundColor,
											 "Game over",
											 Color::Red,
											 DefaultTitleTextSize);

	Button _retryButton = Button(RetryButtonPosition,
								 DefaultButtonWidth,
								 DefaultButtonHeight,
								 Button::DefaultBackgroundColor,
								 Button::DefaultBorderColor,
								 "Retry",
								 Button::ActiveTextColor,
								 Button::DefaultTextSize);

	Button _exitButton = Button(ExitButtonPosition,
								DefaultButtonWidth,
								DefaultButtonHeight,
								Button::DefaultBackgroundColor,
								Button::DefaultBorderColor,
								"Exit",
								Button::ActiveTextColor,
								Button::DefaultTextSize);

public:
	GameOverMenu();

	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;

	void OnMouseDown(const SDL_Event& e);

	void OnQuit(const SDL_Event& e);
};