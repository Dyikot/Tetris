#include "Button.h"

void Button::Show()
{
	SDL_Rect border =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};
	SDL_Rect text =
	{
		.x = _position.x + _width / 4,
		.y = _position.y + _height / 4,
		.w = _width / 2,
		.h = _height / 2 
	};

	Color::SetRenderColor(_renderer, _borderColor);
	SDL_RenderDrawRect(_renderer, &border);
	SDL_RenderCopy(_renderer, _textTexture, NULL, &text);
}
