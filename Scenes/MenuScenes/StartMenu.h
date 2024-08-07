#pragma once

#include <algorithm>

#include "../Scene.h"
#include "../GameScene.h"
#include "../../Application/Application.h"
#include "../../Objects/Controls/Button.h"
#include "../../Objects/Controls/TextBlock.h"
#include "Menu.h"

class StartMenu : public Scene, protected Menu
{
private:
	const int StartButtonOrder = 0;
	const SDL_Point StartGameButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonYPosition(StartButtonOrder)
	};

	const int SettingsButtonOrder = 1;
	const SDL_Point SettingsButtonPosition =
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonYPosition(SettingsButtonOrder)
	};

	const int ExitButtonOrder = 2;
	const SDL_Point ExitButtonPosition = 
	{
		.x = DefaultButtonXPosition,
		.y = CalculateButtonYPosition(ExitButtonOrder)
	};
	
	TextBlock _title = TextBlock(DefaultTitlePosition,
								 Object::DefaultBackgroundColor,
								 "Tetris",
								 TextBlock::ActiveTextColor,
								 DefaultTitleTextSize);

	Button _startGameButton = Button(StartGameButtonPosition,
									 DefaultButtonWidth,
									 DefaultButtonHeight,
									 Button::DefaultBackgroundColor,
									 Button::DefaultBorderColor,
									 "Play",
									 Button::ActiveTextColor,
									 Button::DefaultTextSize);

	Button _settingsButton = Button(SettingsButtonPosition,
									DefaultButtonWidth,
									DefaultButtonHeight,
									Button::DefaultBackgroundColor,
									Button::DefaultBorderColor,
									"Settins",
									Button::InactiveTextColor,
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
	StartMenu();

	void Show() override;

	void HandleEvent(const SDL_Event& e) override;

	void Process() override;

	void OnMouseDown(const SDL_Event& e);

	void OnQuit(const SDL_Event& e);
};