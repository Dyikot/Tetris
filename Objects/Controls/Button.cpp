#include "Button.h"

void Button::Show()
{
	SDL_Rect rectangle =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	int w, h;
	SDL_QueryTexture(_textTexture, NULL, NULL, &w, &h);

	SDL_Rect textRectangle =
	{
		.x = _position.x + _width / 2 - w / 2,
		.y = _position.y + _height / 2 - h / 2,
		.w = w,
		.h = h
	};

	// Border
	Color::SetRenderColor(_renderer, _borderColor);
	SDL_RenderDrawRect(_renderer, &rectangle);

	// Backgroud
	Color::SetRenderColor(_renderer, _backgroud);
	SDL_RenderFillRect(_renderer, &rectangle);

	// Text
	SDL_RenderCopy(_renderer, _textTexture, NULL, &textRectangle);
}

void Button::SetBackground(Colors color)
{
	_backgroud = _backgroundSaved = color;
}

void Button::OnHover()
{
	_backgroud = Colors::Green;
}

void Button::OnLeave()
{
	_backgroud = _backgroundSaved;
}
