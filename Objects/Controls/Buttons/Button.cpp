#include "Button.h"


Button::Button(const SDL_Point& position,
	int width, 
	int height, 
	Color background,
	Color borderColor, 
	Control* content) noexcept:
	Control(position, width, height, background),
	_borderColor(borderColor),
	_backgroundSaved(background),
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

void Button::SetBackground(Color color) noexcept
{
	Object::SetBackground(color);
	_backgroundSaved = color;
}

void Button::SetPosition(const SDL_Point& position) noexcept
{
	Control::SetPosition(position);
}

void Button::SetContent(Control* content) noexcept
{
	_content = content;
}

const Control* Button::GetContent() const
{
	return _content;
}

Control* Button::GetContent() noexcept
{
	return _content;
}

void Button::OnHover() noexcept
{
	_backgroud = Color::Green;
}

void Button::OnLeave() noexcept
{
	_backgroud = _backgroundSaved;
}
