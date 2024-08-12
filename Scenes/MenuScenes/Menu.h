#pragma once

#include <vector>

#include "../../Application/Application.h"
#include "../../Objects/Controls/Buttons/TextButton.h"

class Menu
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
protected:
	std::vector<Button*> _buttons;
	std::vector<Control*> _controls;

	Button* _hoverButton = nullptr;
public:
	int CalculateButtonVerticalPosition(const int order);

	void OnMouseMove(const SDL_Event& e);

	void OnMouseDown(const SDL_Event& e);

	void ShowControls() const noexcept;
};