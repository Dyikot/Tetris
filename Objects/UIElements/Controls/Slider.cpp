#include "Slider.h"

Slider::Slider(const SDL_Point& position,
			   int width, 
			   int height, 
			   Color background,
			   size_t filling) noexcept:
	Control(position, width, height, background),
	ThumbWidth(width / 10),
	ThumbHeight(height * 1.25),
	StartThumbXPosition(position.x),
	EndThumbXPosition(position.x + width)
{
	if(filling > 100)
	{
		filling = 100;
	}

	_thumbPosition = 
	{ 
		.x = StartThumbXPosition + static_cast<int>(static_cast<double>(filling) 
													/ static_cast<double>(Full) * width),
		.y = position.y + height / 2 - ThumbHeight / 2 
	};
}

void Slider::Show() const noexcept
{
	SDL_Rect border =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	SDL_Rect bar =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _thumbPosition.x - _position.x,
		.h = _height
	};

	SDL_Rect thumb =
	{
		.x = _thumbPosition.x - ThumbWidth / 2,
		.y = _thumbPosition.y,
		.w = ThumbWidth,
		.h = ThumbHeight
	};

	// Bar
	Colors::SetRenderColor(_renderer, _backgroud);
	SDL_RenderFillRect(_renderer, &bar);

	// Border
	Colors::SetRenderColor(_renderer, BorderColor);
	SDL_RenderDrawRect(_renderer, &border);

	// Thumb
	Colors::SetRenderColor(_renderer, ThumbColor);
	SDL_RenderFillRect(_renderer, &thumb);
}

void Slider::MoveThumbTo(const int x) noexcept
{
	if(x > StartThumbXPosition && x < EndThumbXPosition)
	{
		_thumbPosition.x = x;
	}
}

size_t Slider::GetFilling() const noexcept
{
	return (_thumbPosition.x - StartThumbXPosition) * 100
		   / (EndThumbXPosition - StartThumbXPosition);
}

void Slider::SetFilling(size_t filling) noexcept
{
	MoveThumbTo(filling * (EndThumbXPosition - StartThumbXPosition) / 100 
				+ StartThumbXPosition);
}
