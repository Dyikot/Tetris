#pragma once

#include <vector>

#include "../../Application/Application.h"
#include "Scene.h"
#include "../Controls/TextButton.h"

class MenuScene: public Scene
{
protected:	
	static constexpr int FirstControlVerticalPosition = 300;	
	static constexpr int FontSizeH1 = 72;
	static constexpr int FontSizeH2 = 60;
	static constexpr int FontSizeH3 = 48;
	static constexpr int FontSizeH4 = 36;
	static constexpr int VerticalSpacing = 10;
	static constexpr Style NavigationButtonStyle = 
	{
		.Width = 120,
		.Height = 40,
		.FontSize = 24,
		.Background = Colors::Transparent,
		.BackgroundOnHover = Colors::Green,
		.BorderColor = Colors::Green,
		.FontColor = Colors::Whitesmoke
	};
	static constexpr Style TitleStyle =
	{
		.FontSize = FontSizeH1,
		.Background = Colors::Transparent,
		.FontColor = Colors::Whitesmoke
	};
	const int NavigationButtonVerticalPosition = Application::Current()->WindowWidth / 2
												 - NavigationButtonStyle.Width / 2;

	std::vector<Button*> _navigationButtons;
	Button* _hoverButton = nullptr;
	TextBlock _title = TextBlock({ Application::Current()->WindowWidth / 2 , 200 },
								 "Title",
								 TitleStyle);
public:
	virtual ~MenuScene() = default;

	void SetBackground() override;

	void Process() override;

	int CalculateButtonVerticalPosition(const int order);
protected:
	virtual void OnMouseMove(const SDL_MouseButtonEvent& e) override;

	virtual void OnMouseDown(const SDL_MouseButtonEvent& e) override;
};