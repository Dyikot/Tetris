#include "MenuScene.h"

int MenuScene::CalculateButtonVerticalPosition(const int order)
{
    return FirstControlVerticalPosition 
		   + order * (DefaultButtonHeight + VerticalSpacing);
}

void MenuScene::SetBackground()
{
	Colors::SetRenderColor(_renderer, Color::Black);
}

void MenuScene::Process()
{

}

void MenuScene::OnMouseMove(const SDL_MouseButtonEvent& e)
{
	UIElement::OnMouseMove(e);

	for(auto button : NavigationButtons)
	{
		if(button->IsMouseOver(e))
		{
			button->OnMouseEnter(e);
			_hoverButton = button;
			return;
		}
		else
		{
			button->OnMouseLeave(e);
		}
	}

	_hoverButton = nullptr;
}

void MenuScene::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	UIElement::OnMouseDown(e);

	if(_hoverButton == nullptr)
	{
		return;
	}

	_hoverButton->OnMouseLeave(e);
	_hoverButton->OnClick(e);
}