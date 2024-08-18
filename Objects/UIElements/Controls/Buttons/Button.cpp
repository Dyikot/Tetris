#include "Button.h"


Button::Button(const SDL_Point& position,
	int width, 
	int height, 
	Color background,
	Color borderColor, 
	Control* content) noexcept:
	Control(position, width, height, background),
	_borderColor(borderColor),
	_content(content)
{
	
}

void Button::Show() const
{
	SDL_Rect rectangle =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	// Border
	Colors::SetRenderColor(_renderer, _borderColor);
	SDL_RenderDrawRect(_renderer, &rectangle);

	// Backgroud
	Colors::SetRenderColor(_renderer, _backgroud);
	SDL_RenderFillRect(_renderer, &rectangle);

	// Content
	_content->Show();
}


void Button::SetContent(Control* content) noexcept
{
	_content = content;
}

Control* const Button::GetContent() const
{
	return _content;
}

void Button::OnClick(const SDL_MouseButtonEvent& e)
{
	if(Click)
	{
		Click(this, e);
	}
}
