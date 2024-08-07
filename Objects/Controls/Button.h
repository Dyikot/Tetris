#pragma once

#include "TextBlock.h"

class Button: public TextBlock
{
public:
	static constexpr int DefaultTextSize = 24;
	static constexpr Color DefaultBorderColor = Color::Green;
protected:
	Color _borderColor;
	Color _backgroundSaved;
public:
	Button(const SDL_Point& position,
		   int width,
		   int height,
		   Color background,
		   Color borderColor,
		   const std::string& text,
		   Color textColor,
		   int textSize) noexcept;

	void Show() noexcept override;

	void SetBackground(Color color) noexcept override;
	
	void OnHover() noexcept;

	void OnLeave() noexcept;
};