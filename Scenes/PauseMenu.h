#pragma once

#include "Scene.h"
#include "../Application/Application.h"
#include "..\Objects\Controls\Button.h"
#include "..\Objects\Controls\TextBlock.h"
#include "..\UI\Menu.h"

class PauseMenu: public Scene, protected Menu
{
private:
	const int ContinueButtonOrder = 0;
	const Coordinates ContinueButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonYPosition(ContinueButtonOrder)
	};

	const int ExitButtonOrder = 1;
	const Coordinates ExitButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonYPosition(ExitButtonOrder)
	};

	TextBlock _pauseTextBlock = TextBlock(DefaultTitlePosition,
										  Object::DefaultBackgroundColor,
										  "Pause",
										  TextBlock::ActiveTextColor,
										  DefaultTitleTextSize);

	Button _continueButton = Button(ContinueButtonPosition,
									DefaultButtonWidth,
									DefaultButtonHeight,
									Button::DefaultBackgroundColor,
									Button::DefaultBorderColor,
									"Continue",
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
	PauseMenu();

	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;

	void OnMouseDown(const SDL_Event& e);

	void OnQuit(const SDL_Event& e);

	void OnKeyDown(const SDL_Event& e);
};