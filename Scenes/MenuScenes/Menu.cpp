#include "Menu.h"

int Menu::CalculateButtonVerticalPosition(const int order)
{
    return FirstControlVerticalPosition 
		   + order * (DefaultButtonHeight + VerticalSpacing);
}

void Menu::OnMouseMove(const SDL_Event& e)
{
	for(auto button : _buttons)
	{
		if(button->IsInRange(e.button.x, e.button.y))
		{
			button->OnHover();
			_hoverButton = button;
			break;
		}
		else
		{
			button->OnLeave();
			_hoverButton = nullptr;
		}
	}
}

void Menu::OnMouseDown(const SDL_Event& e)
{
	if(_hoverButton == nullptr)
	{
		return;
	}

	_hoverButton->OnLeave();
}

void Menu::ShowControls() const noexcept
{
	for(auto control : _controls)
	{
		control->Show();
	}
}
