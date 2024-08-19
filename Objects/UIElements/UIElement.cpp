#include "UIElement.h"

UIElement::UIElement(Color background) noexcept:
	Object(background)
{

}

void UIElement::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	if(MouseDown)
	{
		MouseDown(this, e);
	}
}

void UIElement::OnMouseMove(const SDL_MouseButtonEvent& e)
{
	if(MouseMove)
	{
		MouseMove(this, e);
	}
}

void UIElement::OnKeyDown(const SDL_KeyboardEvent& e)
{
	if(KeyDown)
	{
		KeyDown(this, e);
	}
}

void UIElement::OnKeyHold(const SDL_KeyboardEvent& e)
{
	if(KeyHold)
	{
		KeyHold(this, e);
	}
}
