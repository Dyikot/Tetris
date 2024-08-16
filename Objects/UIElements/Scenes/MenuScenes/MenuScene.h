#pragma once

#include <vector>

#include "../../Application/Application.h"
#include "../Scene.h"
#include "../../Controls/Buttons/TextButton.h"

class MenuScene: public Scene
{
public:
	static constexpr int DefaultButtonWidth = 120;
	static constexpr int DefaultButtonHeight = 40;
	static constexpr int FirstControlVerticalPosition = 300;	
	static constexpr int Header1TextSize = 72;
	static constexpr int Header2TextSize = 60;
	static constexpr int Header3TextSize = 48;
	static constexpr int Header4TextSize = 36;
	static constexpr int VerticalSpacing = 10;

	const int DefaultButtonXPosition = Application::Current()->WindowWidth / 2
		- DefaultButtonWidth / 2;

	const SDL_Point MainTitlePosition =
	{
		.x = Application::Current()->WindowWidth / 2,
		.y = 200
	};
	
	std::vector<Button*> NavigationButtons;
protected:
	Button* _hoverButton = nullptr;
public:
	virtual ~MenuScene() = default;

	int CalculateButtonVerticalPosition(const int order);

	void SetBackground() override;

	void Process() override;
protected:
	virtual void OnMouseMove(const SDL_MouseButtonEvent& e) override;

	virtual void OnMouseDown(const SDL_MouseButtonEvent& e) override;
};