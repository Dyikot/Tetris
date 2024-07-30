#pragma once

#include <vector>

#include "..\Application\Application.h"
#include "..\BasicStructs\Coordinates.h"
#include "..\Objects\Controls\Button.h"

class Menu
{
public:
	const int DefaultButtonWidth = 120;
	const int DefaultButtonHeight = 40;
	const int DefaultButtonXPosition = Application::Current()->WindowWidth / 2 
									   - DefaultButtonWidth / 2;
	const int DefaultButtonYPosition = 300;
	
	const int DefaultTitleTextSize = 72;
	const Coordinates DefaultTitlePosition =
	{
		.x = Application::Current()->WindowWidth / 2,
		.y = 200
	};

	std::vector<Button*> _buttons;
private:
	const int ButtonSpacing = 50;
public:
	int CalculateButtonYPosition(const int order);

	void OnMouseMove(int x, int y);
};