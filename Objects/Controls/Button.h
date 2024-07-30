#pragma once

#include "TextBlock.h"

class Button: public TextBlock
{
public:
	static constexpr int DefaultTextSize = 24;
	static constexpr Colors DefaultBorderColor = Colors::Green;
protected:
	Colors _borderColor;
public:
	Button(const Coordinates& position,
		   int width,
		   int height,
		   Colors background,
		   Colors borderColor,
		   const std::string& text,
		   Colors textColor,
		   int textSize
	):
		TextBlock(position, width, height, background, text, textColor, textSize),
		_borderColor(borderColor){}

	void Show() override;
};