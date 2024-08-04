#include "Button.h"

Button::Button(const Coordinates& position, 
			   int width, 
			   int height,
			   Color background,
			   Color borderColor,
			   const std::string& text,
			   Color textColor, 
			   int textSize):
	TextBlock(position, width, height, background, text, textColor, textSize),
	_borderColor(borderColor),
	_backgroundSaved(background)
{

}

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
	Colors::SetRenderColor(_renderer, _borderColor);
	SDL_RenderDrawRect(_renderer, &rectangle);

	// Backgroud
	Colors::SetRenderColor(_renderer, _backgroud);
	SDL_RenderFillRect(_renderer, &rectangle);

	// Text
	SDL_RenderCopy(_renderer, _textTexture, NULL, &textRectangle);
}

void Button::SetBackground(Color color)
{
	_backgroud = _backgroundSaved = color;
}

void Button::OnHover()
{
	_backgroud = Color::Green;
}

void Button::OnLeave()
{
	_backgroud = _backgroundSaved;
}
