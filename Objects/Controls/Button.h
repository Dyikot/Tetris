#pragma once

#include "TextBlock.h"

class Button: public TextBlock
{
public:
	static constexpr int DefaultTextSize = 24;
	static constexpr Colors DefaultBorderColor = Colors::Green;
protected:
	Colors _borderColor;
	Colors _backgroundSaved;
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
		_borderColor(borderColor),
		_backgroundSaved(background){}

	void Show() override;

	void SetBackground(Colors color) override;
	
	void OnHover();

	void OnLeave();
};