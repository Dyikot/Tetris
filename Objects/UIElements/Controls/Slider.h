#pragma once

#include "Control.h"

class Slider: public Control
{
public:
	static constexpr SDL_Color DefaultColor = Colors::Green;
	static constexpr size_t Full = 100;
protected:
	const SDL_Color ThumbColor = Colors::Whitesmoke;
	const SDL_Color BorderColor = Colors::Green;
	const int ThumbWidth;
	const int ThumbHeight;	
	const int StartThumbXPosition;
	const int EndThumbXPosition;
	SDL_Point _thumbPosition;
public:
	Slider(const SDL_Point& position,
		   int width,
		   int height,
		   const SDL_Color& background,
		   size_t filling = Full) noexcept;

	void Show() const noexcept override;

	void MoveThumbTo(const int x) noexcept;

	void SetFilling(size_t filling) noexcept;

	/// <returns>������� ���������� 0 - 100 %</returns>
	size_t GetFilling() const noexcept;
};