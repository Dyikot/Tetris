#include "Menu.h"

int Menu::CalculateButtonYPosition(const int order)
{
    return DefaultButtonYPosition + order * ButtonSpacing;
}

void Menu::OnMouseMove(int x, int y)
{
	for(auto button : _buttons)
	{
		if(button->IsInRange(x, y))
		{
			button->OnHover();
			break;
		}
		else
		{
			button->OnLeave();
		}
	}
}
