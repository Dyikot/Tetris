#include "Menu.h"

int Menu::CalculateButtonYPosition(const int order)
{
    return DefaultButtonYPosition + order * ButtonSpacing;
}

void Menu::OnMouseMove(const SDL_Event& e)
{
	for(auto button : _buttons)
	{
		if(button->IsInRange(e.button.x, e.button.y))
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
