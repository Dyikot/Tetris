#pragma once

#include "Control.h"

class Slider: public Control
{
public:
	static constexpr Color DefaultColor = Color::Green;
	static constexpr size_t Full = 100;
protected:
	const Color ThumbColor = Color::Whitesmoke;
	const Color BorderColor = Color::Green;

	const int ThumbWidth;
	const int ThumbHeight;
	
	const int StartThumbXPosition;
	const int EndThumbXPosition;

	SDL_Point _thumbPosition;
public:
	Slider(const SDL_Point& position,
		   int width,
		   int height,
		   Color background,
		   size_t filling = Full) noexcept;

	void Show() const noexcept override;

	void MoveThumbTo(const int x) noexcept;

	/// <returns>процент заполнения 0 - 100 %</returns>
	size_t GetFilling() const noexcept;

	void SetFilling(size_t filling) noexcept;
};